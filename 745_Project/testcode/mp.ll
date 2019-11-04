; ModuleID = 'mp.cpp'
source_filename = "mp.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%class.MyClass = type { i32, i32 }

$_ZN7MyClass5printEv = comdat any

$_ZN7MyClassC2Eii = comdat any

@.str = private unnamed_addr constant [19 x i8] c"MyClass %d and %d\0A\00", align 1

; Function Attrs: noinline norecurse optnone uwtable
define i32 @main(i32 %argc, i8** %argv) #0 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %pmf = alloca { i64, i64 }, align 8
  %myclass = alloca %class.MyClass, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  store i8** %argv, i8*** %argv.addr, align 8
  store { i64, i64 } { i64 ptrtoint (void (%class.MyClass*)* @_ZN7MyClass5printEv to i64), i64 0 }, { i64, i64 }* %pmf, align 8
  call void @_ZN7MyClassC2Eii(%class.MyClass* %myclass, i32 10, i32 20) #4
  %0 = load { i64, i64 }, { i64, i64 }* %pmf, align 8
  %memptr.adj = extractvalue { i64, i64 } %0, 1
  %1 = bitcast %class.MyClass* %myclass to i8*
  %2 = getelementptr inbounds i8, i8* %1, i64 %memptr.adj
  %this.adjusted = bitcast i8* %2 to %class.MyClass*
  %memptr.ptr = extractvalue { i64, i64 } %0, 0
  %3 = and i64 %memptr.ptr, 1
  %memptr.isvirtual = icmp ne i64 %3, 0
  br i1 %memptr.isvirtual, label %memptr.virtual, label %memptr.nonvirtual

memptr.virtual:                                   ; preds = %entry
  %4 = bitcast %class.MyClass* %this.adjusted to i8**
  %vtable = load i8*, i8** %4, align 8
  %5 = sub i64 %memptr.ptr, 1
  %6 = getelementptr i8, i8* %vtable, i64 %5
  %7 = bitcast i8* %6 to void (%class.MyClass*)**
  %memptr.virtualfn = load void (%class.MyClass*)*, void (%class.MyClass*)** %7, align 8
  br label %memptr.end

memptr.nonvirtual:                                ; preds = %entry
  %memptr.nonvirtualfn = inttoptr i64 %memptr.ptr to void (%class.MyClass*)*
  br label %memptr.end

memptr.end:                                       ; preds = %memptr.nonvirtual, %memptr.virtual
  %8 = phi void (%class.MyClass*)* [ %memptr.virtualfn, %memptr.virtual ], [ %memptr.nonvirtualfn, %memptr.nonvirtual ]
  call void %8(%class.MyClass* %this.adjusted) #4
  %9 = load i32, i32* %retval, align 4
  ret i32 %9
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr void @_ZN7MyClass5printEv(%class.MyClass* %this) #1 comdat align 2 {
entry:
  %this.addr = alloca %class.MyClass*, align 8
  store %class.MyClass* %this, %class.MyClass** %this.addr, align 8
  %this1 = load %class.MyClass*, %class.MyClass** %this.addr, align 8
  %_a = getelementptr inbounds %class.MyClass, %class.MyClass* %this1, i32 0, i32 0
  %0 = load i32, i32* %_a, align 4
  %_b = getelementptr inbounds %class.MyClass, %class.MyClass* %this1, i32 0, i32 1
  %1 = load i32, i32* %_b, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0), i32 %0, i32 %1) #4
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr void @_ZN7MyClassC2Eii(%class.MyClass* %this, i32 %a, i32 %b) unnamed_addr #2 comdat align 2 {
entry:
  %this.addr = alloca %class.MyClass*, align 8
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  store %class.MyClass* %this, %class.MyClass** %this.addr, align 8
  store i32 %a, i32* %a.addr, align 4
  store i32 %b, i32* %b.addr, align 4
  %this1 = load %class.MyClass*, %class.MyClass** %this.addr, align 8
  %_a = getelementptr inbounds %class.MyClass, %class.MyClass* %this1, i32 0, i32 0
  %0 = load i32, i32* %a.addr, align 4
  store i32 %0, i32* %_a, align 4
  %_b = getelementptr inbounds %class.MyClass, %class.MyClass* %this1, i32 0, i32 1
  %1 = load i32, i32* %b.addr, align 4
  store i32 %1, i32* %_b, align 4
  ret void
}

declare i32 @printf(i8*, ...) #3

attributes #0 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "function_depth"="0" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "function_depth"="0" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "function_depth"="0" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "function_depth"="0" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "function_depth"="0" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.0 (trunk)"}
