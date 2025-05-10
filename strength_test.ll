; ModuleID = 'strength_test'
source_filename = "strength_test"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 5, ptr %x, align 4
  %y = alloca i32, align 4
  %load = load i32, ptr %x, align 4
  %shltmp = shl i32 %load, 3
  store i32 %shltmp, ptr %y, align 4
  %load1 = load i32, ptr %y, align 4
  ret i32 %load1
}
