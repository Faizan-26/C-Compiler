; ModuleID = 'test'
source_filename = "test"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define i32 @add(i32 %a, i32 %b) local_unnamed_addr #0 {
entry:
  %addtmp = add i32 %b, %a
  ret i32 %addtmp
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define noundef i32 @main() local_unnamed_addr #0 {
entry:
  ret i32 15
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
