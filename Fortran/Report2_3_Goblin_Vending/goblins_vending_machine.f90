! Report #2 - Problem 3: Goblin's Vending Machine
! Modern Fortran (Fortran 2018)
program goblins_vending_machine
    use, intrinsic :: iso_fortran_env, only: input_unit, output_unit, iostat_end, iostat_eor
    implicit none

    ! Menu identifiers: equivalent to C's #define constants.
    integer, parameter :: MENU_EXIT         = 0
    integer, parameter :: MENU_RED_POTION   = 1
    integer, parameter :: MENU_MAGIC_SCROLL = 2
    integer, parameter :: MENU_ELIXIR       = 3

    integer, parameter :: PRICE_RED_POTION   = 1000
    integer, parameter :: PRICE_MAGIC_SCROLL = 2000
    integer, parameter :: PRICE_ELIXIR       = 3000

    integer, parameter :: BLESSING_INTERVAL = 3
    integer, parameter :: DISCOUNT_PERCENT  = 50
    integer, parameter :: PERCENT_BASE      = 100
    integer, parameter :: MIN_BALANCE       = 0

    integer, parameter :: INPUT_OK = 0, INPUT_INVALID = 1, INPUT_EOF = -1
    integer, parameter :: MAX_INPUT_LENGTH = 256

    integer :: balance, menu, price, purchase_count
    integer :: next_purchase, input_result
    logical :: is_blessed

    purchase_count = 0

    ! Obtain a nonnegative starting balance.
    do
        write(output_unit, '(A)', advance='no') 'Insert coins (Current Balance): '
        flush(output_unit)
        call read_integer(balance, input_result)

        if (input_result == INPUT_EOF) then
            print '(A)', ''
            print '(A)', 'Input ended.'
            stop 1
        end if
        if (input_result == INPUT_INVALID) then
            print '(A)', 'Invalid input: enter one nonnegative integer.'
            cycle
        end if
        if (balance < MIN_BALANCE) then
            print '(A)', 'Balance cannot be negative.'
            cycle
        end if
        exit
    end do

    ! Keep offering products until Exit or EOF.
    do
        call print_menu()
        write(output_unit, '(A)', advance='no') 'Select an item: '
        flush(output_unit)
        call read_integer(menu, input_result)

        if (input_result == INPUT_EOF) then
            print '(A)', ''
            print '(A,I0,A)', 'Returning ', balance, ' G. Goodbye!'
            exit
        end if
        if (input_result == INPUT_INVALID) then
            print '(A)', 'Invalid input: enter a menu number.'
            cycle
        end if

        if (menu == MENU_EXIT) then
            print '(A,I0,A)', 'Returning ', balance, ' G. Goodbye!'
            exit
        end if

        price = get_price(menu)
        if (price == 0) then
            print '(A)', 'Invalid menu. Please choose 0 to 3.'
            cycle
        end if

        ! Only successful purchases count toward the blessing.
        next_purchase = purchase_count + 1
        is_blessed = (mod(next_purchase, BLESSING_INTERVAL) == 0)
        if (is_blessed) then
            price = price * (PERCENT_BASE - DISCOUNT_PERCENT) / PERCENT_BASE
        end if

        if (balance < price) then
            print '(A)', 'Not enough balance!'
            cycle
        end if

        balance = balance - price
        purchase_count = purchase_count + 1

        if (is_blessed) then
            print '(A,I0,A)', '*** GOBLIN''S BLESSING! ', DISCOUNT_PERCENT, '% DISCOUNT! ***'
        end if

        select case (menu)
        case (MENU_RED_POTION)
            print '(A,I0,A,I0,A)', '[Purchased] Red Potion for ', price, ' G. Balance: ', balance, ' G'
        case (MENU_MAGIC_SCROLL)
            print '(A,I0,A,I0,A)', '[Purchased] Magic Scroll for ', price, ' G. Balance: ', balance, ' G'
        case (MENU_ELIXIR)
            print '(A,I0,A,I0,A)', '[Purchased] Elixir for ', price, ' G. Balance: ', balance, ' G'
        end select
    end do

contains

    subroutine print_menu()
        print '(A)', ''
        print '(A)', '--- Goblin''s Vending Machine ---'
        print '(I0,A,I0,A)', MENU_RED_POTION,   '. Red Potion (',   PRICE_RED_POTION,   ' G)'
        print '(I0,A,I0,A)', MENU_MAGIC_SCROLL, '. Magic Scroll (', PRICE_MAGIC_SCROLL, ' G)'
        print '(I0,A,I0,A)', MENU_ELIXIR,       '. Elixir (',       PRICE_ELIXIR,       ' G)'
        print '(I0,A)', MENU_EXIT, '. Exit'
        print '(A)', '--------------------------------'
    end subroutine print_menu

    integer function get_price(selection) result(original_price)
        integer, intent(in) :: selection

        select case (selection)
        case (MENU_RED_POTION)
            original_price = PRICE_RED_POTION
        case (MENU_MAGIC_SCROLL)
            original_price = PRICE_MAGIC_SCROLL
        case (MENU_ELIXIR)
            original_price = PRICE_ELIXIR
        case default
            original_price = 0
        end select
    end function get_price

    ! Read the entire physical line. Overlong input is drained, then rejected.
    ! Nonadvancing I/O detects end-of-record instead of silently truncating it.
    subroutine read_integer(value, status)
        integer, intent(out) :: value, status
        character(len=MAX_INPUT_LENGTH) :: line
        character(len=1) :: ch
        integer :: io_status, nread, n
        logical :: too_long

        value = 0
        n = 0
        too_long = .false.

        do
            read(input_unit, '(A)', advance='no', size=nread, iostat=io_status) ch
            if (io_status == iostat_eor) exit
            if (io_status == iostat_end) then
                if (n == 0 .and. .not. too_long) then
                    status = INPUT_EOF
                    return
                end if
                exit
            end if
            if (io_status /= 0) then
                status = INPUT_INVALID
                return
            end if
            if (nread /= 1) cycle

            if (n < MAX_INPUT_LENGTH) then
                n = n + 1
                line(n:n) = ch
            else
                too_long = .true.
            end if
        end do

        if (too_long) then
            status = INPUT_INVALID
            return
        end if

        call parse_integer(line(:n), value, status)
    end subroutine read_integer

    ! Accept exactly one optionally signed decimal integer, plus outer
    ! spaces/tabs/CR. Reject embedded junk and integer overflow.
    subroutine parse_integer(line, value, status)
        character(len=*), intent(in) :: line
        integer, intent(out) :: value, status
        integer :: left, right, first_digit, i, io_status

        value = 0
        status = INPUT_INVALID
        left = 1
        right = len(line)

        do while (left <= right)
            if (.not. is_whitespace(line(left:left))) exit
            left = left + 1
        end do
        do while (right >= left)
            if (.not. is_whitespace(line(right:right))) exit
            right = right - 1
        end do
        if (left > right) return

        first_digit = left
        if (line(first_digit:first_digit) == '+' .or. line(first_digit:first_digit) == '-') then
            first_digit = first_digit + 1
        end if
        if (first_digit > right) return

        do i = first_digit, right
            if (line(i:i) < '0' .or. line(i:i) > '9') return
        end do

        read(line(left:right), *, iostat=io_status) value
        if (io_status == 0) status = INPUT_OK
    end subroutine parse_integer

    logical function is_whitespace(ch)
        character(len=1), intent(in) :: ch
        is_whitespace = (ch == ' ' .or. ch == achar(9) .or. ch == achar(13))
    end function is_whitespace

end program goblins_vending_machine
