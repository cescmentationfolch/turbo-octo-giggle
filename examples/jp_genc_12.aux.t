function f
  params
    _result
    v
  endparams

  vars
    c 10
    i 1
  endvars

     %1 = v
     c = %1
     %2 = 'e'
     writec %2
     %2 = 'n'
     writec %2
     %2 = ' '
     writec %2
     %2 = 'f'
     writec %2
     %2 = '.'
     writec %2
     %2 = ' '
     writec %2
     %2 = 'c'
     writec %2
     %2 = ':'
     writec %2
     %2 = ' '
     writec %2
     %3 = 0
     i = %3
  label while1 :
     %4 = 10
     %5 = i < %4
     ifFalse %5 goto endwhile1
     %6 = c[i]
     writei %6
     %7 = ' '
     writec %7
     %8 = 1
     %9 = i + %8
     i = %9
     goto while1
  label endwhile1 :
     %10 = '\n'
     writec %10
     return
endfunction

function g
  params
    _result
    v
  endparams

  vars
    d 10
    i 1
  endvars

     %1 = 0
     i = %1
  label while1 :
     %2 = 10
     %3 = i < %2
     ifFalse %3 goto endwhile1
     %4 = 1
     %5 = - %4
     d[i] = %5
     %6 = 1
     %7 = i + %6
     i = %7
     goto while1
  label endwhile1 :
     %8 = v
     %8 = d
     return
endfunction

function main
  vars
    a 10
    b 10
    i 1
    j 1
  endvars

     %1 = 0
     i = %1
  label while1 :
     %2 = 10
     %3 = i < %2
     ifFalse %3 goto endwhile1
     a[i] = i
     %4 = 0
     b[i] = %4
     %5 = 1
     %6 = i + %5
     i = %6
     goto while1
  label endwhile1 :
     b = a
     %7 = 'd'
     writec %7
     %7 = 'e'
     writec %7
     %7 = 's'
     writec %7
     %7 = 'p'
     writec %7
     %7 = 'r'
     writec %7
     %7 = 'e'
     writec %7
     %7 = 's'
     writec %7
     %7 = ' '
     writec %7
     %7 = 'd'
     writec %7
     %7 = 'e'
     writec %7
     %7 = ' '
     writec %7
     %7 = 'b'
     writec %7
     %7 = '='
     writec %7
     %7 = 'a'
     writec %7
     %7 = '.'
     writec %7
     %7 = ' '
     writec %7
     %7 = 'b'
     writec %7
     %7 = ':'
     writec %7
     %7 = ' '
     writec %7
     %8 = 0
     i = %8
  label while2 :
     %9 = 10
     %10 = i < %9
     ifFalse %10 goto endwhile2
     %11 = b[i]
     writei %11
     %12 = ' '
     writec %12
     %13 = 1
     %14 = i + %13
     i = %14
     goto while2
  label endwhile2 :
     %15 = '\n'
     writec %15
     %16 = 'd'
     writec %16
     %16 = 'e'
     writec %16
     %16 = 's'
     writec %16
     %16 = 'p'
     writec %16
     %16 = 'r'
     writec %16
     %16 = 'e'
     writec %16
     %16 = 's'
     writec %16
     %16 = ' '
     writec %16
     %16 = 'd'
     writec %16
     %16 = 'e'
     writec %16
     %16 = ' '
     writec %16
     %16 = 'b'
     writec %16
     %16 = '='
     writec %16
     %16 = 'a'
     writec %16
     %16 = '.'
     writec %16
     %16 = ' '
     writec %16
     %16 = 'a'
     writec %16
     %16 = ':'
     writec %16
     %16 = ' '
     writec %16
     %17 = 0
     i = %17
  label while3 :
     %18 = 10
     %19 = i < %18
     ifFalse %19 goto endwhile3
     %20 = a[i]
     writei %20
     %21 = ' '
     writec %21
     %22 = 1
     %23 = i + %22
     i = %23
     goto while3
  label endwhile3 :
     %24 = '\n'
     writec %24
     pushparam 
     %25 = &a
     pushparam %25
     call f
     popparam 
     popparam 
     %26 = 'd'
     writec %26
     %26 = 'e'
     writec %26
     %26 = 's'
     writec %26
     %26 = 'p'
     writec %26
     %26 = 'r'
     writec %26
     %26 = 'e'
     writec %26
     %26 = 's'
     writec %26
     %26 = ' '
     writec %26
     %26 = 'd'
     writec %26
     %26 = 'e'
     writec %26
     %26 = ' '
     writec %26
     %26 = 'f'
     writec %26
     %26 = '('
     writec %26
     %26 = 'a'
     writec %26
     %26 = ')'
     writec %26
     %26 = '.'
     writec %26
     %26 = ' '
     writec %26
     %26 = 'a'
     writec %26
     %26 = ':'
     writec %26
     %26 = ' '
     writec %26
     %27 = 0
     i = %27
  label while4 :
     %28 = 10
     %29 = i < %28
     ifFalse %29 goto endwhile4
     %30 = a[i]
     writei %30
     %31 = ' '
     writec %31
     %32 = 1
     %33 = i + %32
     i = %33
     goto while4
  label endwhile4 :
     %34 = '\n'
     writec %34
     pushparam 
     %35 = &a
     pushparam %35
     call g
     popparam 
     popparam 
     %36 = 'd'
     writec %36
     %36 = 'e'
     writec %36
     %36 = 's'
     writec %36
     %36 = 'p'
     writec %36
     %36 = 'r'
     writec %36
     %36 = 'e'
     writec %36
     %36 = 's'
     writec %36
     %36 = ' '
     writec %36
     %36 = 'd'
     writec %36
     %36 = 'e'
     writec %36
     %36 = ' '
     writec %36
     %36 = 'g'
     writec %36
     %36 = '('
     writec %36
     %36 = 'a'
     writec %36
     %36 = ')'
     writec %36
     %36 = '.'
     writec %36
     %36 = ' '
     writec %36
     %36 = 'a'
     writec %36
     %36 = ':'
     writec %36
     %36 = ' '
     writec %36
     %37 = 0
     i = %37
  label while5 :
     %38 = 10
     %39 = i < %38
     ifFalse %39 goto endwhile5
     %40 = a[i]
     writei %40
     %41 = ' '
     writec %41
     %42 = 1
     %43 = i + %42
     i = %43
     goto while5
  label endwhile5 :
     %44 = '\n'
     writec %44
     return
endfunction


