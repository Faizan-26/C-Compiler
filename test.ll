; ModuleID = 'test'
source_filename = "test"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

declare void @print(i32)

define i32 @add(i32 %a, i32 %b) {
entry:
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  %b2 = alloca i32, align 4
  store i32 %b, ptr %b2, align 4
  %load = load i32, ptr %a1, align 4
  %load3 = load i32, ptr %b2, align 4
  %addtmp = add i32 %load, %load3
  ret i32 %addtmp
}

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 10, ptr %x, align 4
  %y = alloca i32, align 4
  store i32 5, ptr %y, align 4
  %z = alloca i32, align 4
  store i32 42, ptr %z, align 4
  %sum = alloca i32, align 4
  %load = load i32, ptr %x, align 4
  %load1 = load i32, ptr %y, align 4
  %addtmp = add i32 %load, %load1
  store i32 %addtmp, ptr %sum, align 4
  %load2 = load i32, ptr %sum, align 4
  ret i32 %load2
}
