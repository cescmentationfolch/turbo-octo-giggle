function main
  vars
    a 1
    b 1
    c 1
  endvars

   %1 = 13
   a = %1
   %2 = 4
   b = %2
   %3 = a / b
   %3 = b * %3
   %3 = a - %3
   c = %3
   writei c
   %4 = '.'
   writec %4
   %5 = '\n'
   writec %5
   %6 = - a
   %7 = %6 / b
   %7 = b * %7
   %7 = %6 - %7
   c = %7
   writei c
   %8 = '.'
   writec %8
   %9 = '\n'
   writec %9
   %10 = - b
   %11 = a / %10
   %11 = %10 * %11
   %11 = a - %11
   c = %11
   writei c
   %12 = '.'
   writec %12
   %13 = '\n'
   writec %13
   %14 = 3
   %15 = a + %14
   %16 = %15 / b
   %16 = b * %16
   %16 = %15 - %16
   c = %16
   writei c
   %17 = '.'
   writec %17
   %18 = '\n'
   writec %18
   %19 = - a
   %20 = 3
   %21 = %19 - %20
   %22 = - b
   %23 = %21 / %22
   %23 = %22 * %23
   %23 = %21 - %23
   c = %23
   writei c
   %24 = '.'
   writec %24
   %25 = '\n'
   writec %25
   return
endfunction


