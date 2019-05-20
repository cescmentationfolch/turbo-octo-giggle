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
     %2 = 0
     %3 = %1[%2]
     c[%2] = %3
     %2 = 1
     %3 = %1[%2]
     c[%2] = %3
     %2 = 2
     %3 = %1[%2]
     c[%2] = %3
     %2 = 3
     %3 = %1[%2]
     c[%2] = %3
     %2 = 4
     %3 = %1[%2]
     c[%2] = %3
     %2 = 5
     %3 = %1[%2]
     c[%2] = %3
     %2 = 6
     %3 = %1[%2]
     c[%2] = %3
     %2 = 7
     %3 = %1[%2]
     c[%2] = %3
     %2 = 8
     %3 = %1[%2]
     c[%2] = %3
     %2 = 9
     %3 = %1[%2]
     c[%2] = %3
     %4 = 'e'
     writec %4
     %4 = 'n'
     writec %4
     %4 = ' '
     writec %4
     %4 = 'f'
     writec %4
     %4 = '.'
     writec %4
     %4 = ' '
     writec %4
     %4 = 'c'
     writec %4
     %4 = ':'
     writec %4
     %4 = ' '
     writec %4
     %5 = 0
     i = %5
  label while1 :
     %6 = 10
     %7 = i < %6
     ifFalse %7 goto endwhile1
     %8 = c[i]
     writei %8
     %9 = ' '
     writec %9
     %10 = 1
     %11 = i + %10
     i = %11
     goto while1
  label endwhile1 :
     %12 = '\n'
     writec %12
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
     %9 = 0
     %10 = d[%9]
     %8[%9] = %10
     %9 = 1
     %10 = d[%9]
     %8[%9] = %10
     %9 = 2
     %10 = d[%9]
     %8[%9] = %10
     %9 = 3
     %10 = d[%9]
     %8[%9] = %10
     %9 = 4
     %10 = d[%9]
     %8[%9] = %10
     %9 = 5
     %10 = d[%9]
     %8[%9] = %10
     %9 = 6
     %10 = d[%9]
     %8[%9] = %10
     %9 = 7
     %10 = d[%9]
     %8[%9] = %10
     %9 = 8
     %10 = d[%9]
     %8[%9] = %10
     %9 = 9
     %10 = d[%9]
     %8[%9] = %10
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
     %7 = 0
     %8 = a[%7]
     b[%7] = %8
     %7 = 1
     %8 = a[%7]
     b[%7] = %8
     %7 = 2
     %8 = a[%7]
     b[%7] = %8
     %7 = 3
     %8 = a[%7]
     b[%7] = %8
     %7 = 4
     %8 = a[%7]
     b[%7] = %8
     %7 = 5
     %8 = a[%7]
     b[%7] = %8
     %7 = 6
     %8 = a[%7]
     b[%7] = %8
     %7 = 7
     %8 = a[%7]
     b[%7] = %8
     %7 = 8
     %8 = a[%7]
     b[%7] = %8
     %7 = 9
     %8 = a[%7]
     b[%7] = %8
     %9 = 'd'
     writec %9
     %9 = 'e'
     writec %9
     %9 = 's'
     writec %9
     %9 = 'p'
     writec %9
     %9 = 'r'
     writec %9
     %9 = 'e'
     writec %9
     %9 = 's'
     writec %9
     %9 = ' '
     writec %9
     %9 = 'd'
     writec %9
     %9 = 'e'
     writec %9
     %9 = ' '
     writec %9
     %9 = 'b'
     writec %9
     %9 = '='
     writec %9
     %9 = 'a'
     writec %9
     %9 = '.'
     writec %9
     %9 = ' '
     writec %9
     %9 = 'b'
     writec %9
     %9 = ':'
     writec %9
     %9 = ' '
     writec %9
     %10 = 0
     i = %10
  label while2 :
     %11 = 10
     %12 = i < %11
     ifFalse %12 goto endwhile2
     %13 = b[i]
     writei %13
     %14 = ' '
     writec %14
     %15 = 1
     %16 = i + %15
     i = %16
     goto while2
  label endwhile2 :
     %17 = '\n'
     writec %17
     %18 = 'd'
     writec %18
     %18 = 'e'
     writec %18
     %18 = 's'
     writec %18
     %18 = 'p'
     writec %18
     %18 = 'r'
     writec %18
     %18 = 'e'
     writec %18
     %18 = 's'
     writec %18
     %18 = ' '
     writec %18
     %18 = 'd'
     writec %18
     %18 = 'e'
     writec %18
     %18 = ' '
     writec %18
     %18 = 'b'
     writec %18
     %18 = '='
     writec %18
     %18 = 'a'
     writec %18
     %18 = '.'
     writec %18
     %18 = ' '
     writec %18
     %18 = 'a'
     writec %18
     %18 = ':'
     writec %18
     %18 = ' '
     writec %18
     %19 = 0
     i = %19
  label while3 :
     %20 = 10
     %21 = i < %20
     ifFalse %21 goto endwhile3
     %22 = a[i]
     writei %22
     %23 = ' '
     writec %23
     %24 = 1
     %25 = i + %24
     i = %25
     goto while3
  label endwhile3 :
     %26 = '\n'
     writec %26
     pushparam 
     %27 = &a
     pushparam %27
     call f
     popparam 
     popparam 
     %28 = 'd'
     writec %28
     %28 = 'e'
     writec %28
     %28 = 's'
     writec %28
     %28 = 'p'
     writec %28
     %28 = 'r'
     writec %28
     %28 = 'e'
     writec %28
     %28 = 's'
     writec %28
     %28 = ' '
     writec %28
     %28 = 'd'
     writec %28
     %28 = 'e'
     writec %28
     %28 = ' '
     writec %28
     %28 = 'f'
     writec %28
     %28 = '('
     writec %28
     %28 = 'a'
     writec %28
     %28 = ')'
     writec %28
     %28 = '.'
     writec %28
     %28 = ' '
     writec %28
     %28 = 'a'
     writec %28
     %28 = ':'
     writec %28
     %28 = ' '
     writec %28
     %29 = 0
     i = %29
  label while4 :
     %30 = 10
     %31 = i < %30
     ifFalse %31 goto endwhile4
     %32 = a[i]
     writei %32
     %33 = ' '
     writec %33
     %34 = 1
     %35 = i + %34
     i = %35
     goto while4
  label endwhile4 :
     %36 = '\n'
     writec %36
     pushparam 
     %37 = &a
     pushparam %37
     call g
     popparam 
     popparam 
     %38 = 'd'
     writec %38
     %38 = 'e'
     writec %38
     %38 = 's'
     writec %38
     %38 = 'p'
     writec %38
     %38 = 'r'
     writec %38
     %38 = 'e'
     writec %38
     %38 = 's'
     writec %38
     %38 = ' '
     writec %38
     %38 = 'd'
     writec %38
     %38 = 'e'
     writec %38
     %38 = ' '
     writec %38
     %38 = 'g'
     writec %38
     %38 = '('
     writec %38
     %38 = 'a'
     writec %38
     %38 = ')'
     writec %38
     %38 = '.'
     writec %38
     %38 = ' '
     writec %38
     %38 = 'a'
     writec %38
     %38 = ':'
     writec %38
     %38 = ' '
     writec %38
     %39 = 0
     i = %39
  label while5 :
     %40 = 10
     %41 = i < %40
     ifFalse %41 goto endwhile5
     %42 = a[i]
     writei %42
     %43 = ' '
     writec %43
     %44 = 1
     %45 = i + %44
     i = %45
     goto while5
  label endwhile5 :
     %46 = '\n'
     writec %46
     return
endfunction


