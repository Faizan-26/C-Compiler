; ModuleID = 'strength_test'
source_filename = "strength_test"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define noundef i32 @main() local_unnamed_addr #0 {
entry:
  ret i32 40
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
