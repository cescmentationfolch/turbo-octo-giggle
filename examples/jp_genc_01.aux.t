function main
  vars
    a 1
    b 1
    end 1
    pi 1
  endvars

   %1 = 12
   a = %1
   %2 = 5
   %3 = a * %2
   %4 = 1
   %5 = a + %4
   %6 = a * %5
   %7 = %3 + %6
   b = %7
   %8 = a <= b
   %9 = 0
   %10 = a == %9
   %11 = not %10
   %12 = %8 and %11
   end = %12
   %13 = 3.3
   %14 = 1
   %15 = %14 / a
   %17 = float %15
   %16 = %13 +. %17
   %18 = 2.0
   %19 = -. %18
   %21 = float a
   %20 = %19 /. %21
   %22 = %16 -. %20
   pi = %22
   %23 = a == b
   %24 = %23 or end
   writei %24
   writeln
   %26 = a * b
   writei %26
   writeln
   %28 = 2
   %30 = float %28
   %29 = %30 *. pi
   writef %29
   writeln
   return
endfunction


