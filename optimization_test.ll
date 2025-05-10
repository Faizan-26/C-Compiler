; ModuleID = 'optimization_test'
source_filename = "optimization_test"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 5, ptr %x, align 4
  %result1 = alloca i32, align 4
  store i32 0, ptr %result1, align 4
  %result2 = alloca i32, align 4
  store i32 0, ptr %result2, align 4
  %load = load i32, ptr %result1, align 4
  %load1 = load i32, ptr %result2, align 4
  %addtmp = add i32 %load, %load1
  ret i32 %addtmp
}
