@echo off

if exist C:\Keil\ARM\BIN40\fromelf.exe (
if exist .\..\MDK-ARM\STM3210C-EVAL\STM3210C-EVAL.axf (C:\Keil\ARM\BIN40\fromelf.exe ".\..\MDK-ARM\STM3210C-EVAL\STM3210C-EVAL.axf" --bin --output ".\STM3210C-EVAL_SysTick.bin")  

 )

pause

