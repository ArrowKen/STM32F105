@echo off

if exist .\..\TrueSTUDIO\STM3210C-EVAL\Debug\STM3210C-EVAL.elf  ("arm-elf-objcopy.exe" -O binary ".\..\TrueSTUDIO\STM3210C-EVAL\Debug\STM3210C-EVAL.elf" ".\..\TrueSTUDIO\STM3210C-EVAL\Debug\STM3210C-EVAL_SysTick.bin")

pause

