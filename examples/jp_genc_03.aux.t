function mul
  params
    _result
    a
    b
  endparams

   %1 = a * b
   _result = %1
   return
   return
endfunction

function main
  vars
    x 1
    y 1
  endvars

   readi x
   readi y
   %1 = 'x'
   writec %1
   %1 = '*'
   writec %1
   %1 = 'y'
   writec %1
   %1 = '*'
   writec %1
   %1 = '2'
   writec %1
   %1 = '='
   writec %1
   pushparam 
   pushparam x
   pushparam y
   call mul
   popparam 
   popparam 
   popparam %2
   %3 = 2
   %4 = %2 * %3
   writei %4
   %5 = '.'
   writec %5
   writeln
   return
endfunction


