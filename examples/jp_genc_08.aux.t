function x2
  params
    _result
    a
  endparams

  vars
    i 1
    n 1
  endvars

     %1 = 0
     n = %1
     %2 = 0
     i = %2
  label while1 :
     %3 = 10
     %4 = i < %3
     ifFalse %4 goto endwhile1
     %5 = a
     %6 = %5[i]
     %7 = 0
     %8 = %6 == %7
     ifFalse %8 goto endif1
     %9 = 1
     %10 = n + %9
     n = %10
  label endif1 :
     %11 = a
     %12 = a
     %13 = %12[i]
     %14 = 2
     %15 = %13 * %14
     %11[i] = %15
     %16 = a
     %17 = %16[i]
     writei %17
     writeln
     %19 = 1
     %20 = i + %19
     i = %20
     goto while1
  label endwhile1 :
     _result = n
     return
     return
endfunction

function main
  vars
    x 10
    i 1
    z 1
  endvars

     %1 = 0
     i = %1
  label while1 :
     %2 = 10
     %3 = i < %2
     ifFalse %3 goto endwhile1
     x[i] = i
     %4 = 1
     %5 = i + %4
     i = %5
     goto while1
  label endwhile1 :
     %6 = 0
     i = %6
  label while2 :
     %7 = 10
     %8 = i < %7
     ifFalse %8 goto endwhile2
     %9 = x[i]
     writei %9
     writeln
     %11 = 1
     %12 = i + %11
     i = %12
     goto while2
  label endwhile2 :
     pushparam 
     %13 = &x
     pushparam %13
     call x2
     popparam 
     popparam %14
     z = %14
     %15 = 'z'
     writec %15
     %15 = ':'
     writec %15
     writei z
     writeln
     %17 = 0
     i = %17
  label while3 :
     %18 = 10
     %19 = i < %18
     ifFalse %19 goto endwhile3
     %20 = 'x'
     writec %20
     %20 = '['
     writec %20
     writei i
     %21 = ']'
     writec %21
     %21 = '='
     writec %21
     %22 = x[i]
     writei %22
     writeln
     %24 = 1
     %25 = i + %24
     i = %25
     goto while3
  label endwhile3 :
     return
endfunction


