function f1
  params
    _result
    a
    b
  endparams

  vars
    c 1
    d 1
    found 1
  endvars

     %1 = 0
     found = %1
     %2 = 0.7
     %4 = float a
     %3 = %4 +. %2
     c = %3
     %5 = 0
     d = %5
     %6 = a + d
     %8 = float %6
     %7 = c <. %8
     %9 = not found
     %10 = %7 or %9
     ifFalse %10 goto endif1
  label while1 :
     %11 = 0
     %12 = %11 < b
     ifFalse %12 goto endwhile1
     %13 = 1
     %14 = b - %13
     b = %14
     %15 = 1
     found = %15
     goto while1
  label endwhile1 :
  label endif1 :
     %16 = 11
     %17 = b <= %16
     ifFalse %17 goto endif2
     %18 = 2
     %20 = float %18
     %19 = %20 *. c
     %21 = 1
     %23 = float %21
     %22 = %19 +. %23
     c = %22
  label endif2 :
     writef c
     writeln
     return
endfunction

function main
  vars
    a 1
    b 1
  endvars

   %1 = 4
   a = %1
   %2 = 2
   %3 = %2 * a
   %4 = 1
   %5 = %3 + %4
   b = %5
   pushparam 
   pushparam b
   %6 = 3
   %7 = %6 + b
   pushparam %7
   call f1
   popparam 
   popparam 
   popparam 
   return
endfunction


