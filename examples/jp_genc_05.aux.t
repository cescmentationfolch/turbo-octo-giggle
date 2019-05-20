function f
  params
    _result
    a
    b
  endparams

  vars
    x 1
    y 1
    z 10
  endvars

     %1 = 9
     %2 = 67
     %3 = a + %2
     z[%1] = %3
     %4 = 34
     x = %4
     %5 = 3
     %6 = 56
     %7 = 9
     %8 = z[%7]
     %9 = %6 + %8
     z[%5] = %9
     %10 = 3
     %11 = z[%10]
     %12 = x < %11
     ifFalse %12 goto else1
     %13 = 78
     x = %13
     writef b
     writeln
     goto endif1
  label else1 :
     %15 = 99
     x = %15
  label endif1 :
     %16 = 3
     %17 = z[%16]
     writei %17
     writeln
     %19 = 1
     _result = %19
     return
     return
endfunction

function fz
  params
    _result
    r
  endparams

  label while1 :
     %1 = 0
     %2 = %1 < r
     ifFalse %2 goto endwhile1
     %3 = 1
     %4 = r - %3
     r = %4
     goto while1
  label endwhile1 :
     return
endfunction

function main
  vars
    a 1
  endvars

     pushparam 
     %1 = 3
     pushparam %1
     %2 = 2
     %3 = float %2
     pushparam %3
     call f
     popparam 
     popparam 
     popparam %4
     ifFalse %4 goto endif1
     %5 = 3.7
     %7 = float a
     %6 = %7 +. %5
     %8 = 4
     %10 = float %8
     %9 = %6 +. %10
     writef %9
     writeln
  label endif1 :
     return
endfunction


