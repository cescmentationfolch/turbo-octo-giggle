function f
  params
    _result
    a
    f
  endparams

  vars
    x 1
    b 1
    z 10
  endvars

     %1 = 5
     readi %2
     z[%1] = %2
     %3 = 5
     %4 = z[%3]
     %5 = 88
     %6 = %4 + %5
     writei %6
     readi b
     readf f
     ifFalse b goto endif1
     %7 = 'h'
     writec %7
     writeln
     %7 = '\t'
     writec %7
     %7 = 'l'
     writec %7
     %7 = '\\'
     writec %7
     %7 = 'a'
     writec %7
     %8 = -. f
     %9 = -. %8
     %10 = -. %9
     writef %10
     writeln
  label endif1 :
     %12 = 1
     _result = %12
     return
     return
endfunction

function fz
  params
    _result
    r
    u
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
     %5 = 0
     %6 = r == %5
     ifFalse %6 goto endif1
     pushparam 
     %7 = 55555
     pushparam %7
     %8 = 1
     %9 = 4
     %10 = %8 / %9
     %11 = float %10
     pushparam %11
     call f
     popparam 
     popparam 
     popparam 
  label endif1 :
     %12 = 3
     %13 = r + %12
     %15 = float %13
     %14 = %15 *. u
     _result = %14
     return
     return
endfunction

function main
  vars
    a 1
    q 1
  endvars

   %1 = 0
   q = %1
   pushparam 
   %2 = 3
   %3 = 4
   %4 = %2 + %3
   pushparam %4
   pushparam 
   %5 = 4444
   pushparam %5
   %6 = 2
   %8 = float %6
   %7 = q +. %8
   pushparam %7
   call fz
   popparam 
   popparam 
   popparam %9
   pushparam %9
   call fz
   popparam 
   popparam 
   popparam %10
   q = %10
   %11 = 3.7
   %12 = q +. %11
   %13 = 4
   %15 = float %13
   %14 = %12 +. %15
   writef %14
   writeln
   return
endfunction


