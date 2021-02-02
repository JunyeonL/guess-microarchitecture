
#include "config.h"
#include "store_buffer.h"

#ifndef __LOAD_BUFFER__
#define __LOAD_BUFFER__

#define LOAD1	START LOOP {ASM_PREFIX MOV(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(1)
#define LOAD2	START LOOP {ASM_PREFIX MOV2(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(2)
#define LOAD3	START LOOP {ASM_PREFIX MOV3(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(3)
#define LOAD4	START LOOP {ASM_PREFIX MOV4(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(4)
#define LOAD5	START LOOP {ASM_PREFIX MOV5(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(5)
#define LOAD6	START LOOP {ASM_PREFIX MOV6(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(6)
#define LOAD7	START LOOP {ASM_PREFIX MOV7(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(7)
#define LOAD8	START LOOP {ASM_PREFIX MOV8(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(8)
#define LOAD9	START LOOP {ASM_PREFIX MOV9(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(9)
#define LOAD10  START LOOP {ASM_PREFIX MOV10(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(10)

#define LOAD11 START LOOP {ASM_PREFIX MOV10(0) MOV(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(11)
#define LOAD12 START LOOP {ASM_PREFIX MOV10(0) MOV2(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(12)
#define LOAD13 START LOOP {ASM_PREFIX MOV10(0) MOV3(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(13)
#define LOAD14 START LOOP {ASM_PREFIX MOV10(0) MOV4(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(14)
#define LOAD15 START LOOP {ASM_PREFIX MOV10(0) MOV5(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(15)
#define LOAD16 START LOOP {ASM_PREFIX MOV10(0) MOV6(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(16)
#define LOAD17 START LOOP {ASM_PREFIX MOV10(0) MOV7(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(17)
#define LOAD18 START LOOP {ASM_PREFIX MOV10(0) MOV8(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(18)
#define LOAD19 START LOOP {ASM_PREFIX MOV10(0) MOV9(10) NOP500 LOAD_ASM_SUFFIX} LOAD_END(19)
#define LOAD20 START LOOP {ASM_PREFIX MOV20(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(20)

#define LOAD21 START LOOP {ASM_PREFIX MOV20(0) MOV(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(21)
#define LOAD22 START LOOP {ASM_PREFIX MOV20(0) MOV2(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(22)
#define LOAD23 START LOOP {ASM_PREFIX MOV20(0) MOV3(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(23)
#define LOAD24 START LOOP {ASM_PREFIX MOV20(0) MOV4(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(24)
#define LOAD25 START LOOP {ASM_PREFIX MOV20(0) MOV5(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(25)
#define LOAD26 START LOOP {ASM_PREFIX MOV20(0) MOV6(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(26)
#define LOAD27 START LOOP {ASM_PREFIX MOV20(0) MOV7(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(27)
#define LOAD28 START LOOP {ASM_PREFIX MOV20(0) MOV8(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(28)
#define LOAD29 START LOOP {ASM_PREFIX MOV20(0) MOV9(20) NOP500 LOAD_ASM_SUFFIX} LOAD_END(29)
#define LOAD30 START LOOP {ASM_PREFIX MOV30(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(30)

#define LOAD31 START LOOP {ASM_PREFIX MOV30(0) MOV(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(31)
#define LOAD32 START LOOP {ASM_PREFIX MOV30(0) MOV2(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(32)
#define LOAD33 START LOOP {ASM_PREFIX MOV30(0) MOV3(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(33)
#define LOAD34 START LOOP {ASM_PREFIX MOV30(0) MOV4(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(34)
#define LOAD35 START LOOP {ASM_PREFIX MOV30(0) MOV5(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(35)
#define LOAD36 START LOOP {ASM_PREFIX MOV30(0) MOV6(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(36)
#define LOAD37 START LOOP {ASM_PREFIX MOV30(0) MOV7(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(37)
#define LOAD38 START LOOP {ASM_PREFIX MOV30(0) MOV8(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(38)
#define LOAD39 START LOOP {ASM_PREFIX MOV30(0) MOV9(30) NOP500 LOAD_ASM_SUFFIX} LOAD_END(39)
#define LOAD40 START LOOP {ASM_PREFIX MOV40(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(40)

#define LOAD41 START LOOP {ASM_PREFIX MOV40(0) MOV(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(41)
#define LOAD42 START LOOP {ASM_PREFIX MOV40(0) MOV2(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(42)
#define LOAD43 START LOOP {ASM_PREFIX MOV40(0) MOV3(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(43)
#define LOAD44 START LOOP {ASM_PREFIX MOV40(0) MOV4(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(44)
#define LOAD45 START LOOP {ASM_PREFIX MOV40(0) MOV5(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(45)
#define LOAD46 START LOOP {ASM_PREFIX MOV40(0) MOV6(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(46)
#define LOAD47 START LOOP {ASM_PREFIX MOV40(0) MOV7(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(47)
#define LOAD48 START LOOP {ASM_PREFIX MOV40(0) MOV8(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(48)
#define LOAD49 START LOOP {ASM_PREFIX MOV40(0) MOV9(40) NOP500 LOAD_ASM_SUFFIX} LOAD_END(49)
#define LOAD50 START LOOP {ASM_PREFIX MOV50(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(50)

#define LOAD51 START LOOP {ASM_PREFIX MOV50(0) MOV(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(51)
#define LOAD52 START LOOP {ASM_PREFIX MOV50(0) MOV2(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(52)
#define LOAD53 START LOOP {ASM_PREFIX MOV50(0) MOV3(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(53)
#define LOAD54 START LOOP {ASM_PREFIX MOV50(0) MOV4(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(54)
#define LOAD55 START LOOP {ASM_PREFIX MOV50(0) MOV5(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(55)
#define LOAD56 START LOOP {ASM_PREFIX MOV50(0) MOV6(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(56)
#define LOAD57 START LOOP {ASM_PREFIX MOV50(0) MOV7(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(57)
#define LOAD58 START LOOP {ASM_PREFIX MOV50(0) MOV8(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(58)
#define LOAD59 START LOOP {ASM_PREFIX MOV50(0) MOV9(50) NOP500 LOAD_ASM_SUFFIX} LOAD_END(59)
#define LOAD60 START LOOP {ASM_PREFIX MOV60(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(60)

#define LOAD61 START LOOP {ASM_PREFIX MOV60(0) MOV(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(61)
#define LOAD62 START LOOP {ASM_PREFIX MOV60(0) MOV2(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(62)
#define LOAD63 START LOOP {ASM_PREFIX MOV60(0) MOV3(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(63)
#define LOAD64 START LOOP {ASM_PREFIX MOV60(0) MOV4(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(64)
#define LOAD65 START LOOP {ASM_PREFIX MOV60(0) MOV5(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(65)
#define LOAD66 START LOOP {ASM_PREFIX MOV60(0) MOV6(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(66)
#define LOAD67 START LOOP {ASM_PREFIX MOV60(0) MOV7(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(67)
#define LOAD68 START LOOP {ASM_PREFIX MOV60(0) MOV8(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(68)
#define LOAD69 START LOOP {ASM_PREFIX MOV60(0) MOV9(60) NOP500 LOAD_ASM_SUFFIX} LOAD_END(69)
#define LOAD70 START LOOP {ASM_PREFIX MOV70(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(70)

#define LOAD71 START LOOP {ASM_PREFIX MOV70(0) MOV(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(71)
#define LOAD72 START LOOP {ASM_PREFIX MOV70(0) MOV2(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(72)
#define LOAD73 START LOOP {ASM_PREFIX MOV70(0) MOV3(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(73)
#define LOAD74 START LOOP {ASM_PREFIX MOV70(0) MOV4(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(74)
#define LOAD75 START LOOP {ASM_PREFIX MOV70(0) MOV5(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(75)
#define LOAD76 START LOOP {ASM_PREFIX MOV70(0) MOV6(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(76)
#define LOAD77 START LOOP {ASM_PREFIX MOV70(0) MOV7(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(77)
#define LOAD78 START LOOP {ASM_PREFIX MOV70(0) MOV8(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(78)
#define LOAD79 START LOOP {ASM_PREFIX MOV70(0) MOV9(70) NOP500 LOAD_ASM_SUFFIX} LOAD_END(79)
#define LOAD80 START LOOP {ASM_PREFIX MOV80(0) NOP500 LOAD_ASM_SUFFIX} LOAD_END(80)

#define LOAD_ASM_SUFFIX :: "m"(*p) : "%rax" );

#if CACHE_DEBUG
#define LOAD_END(a) gap = timestamp() - start; buf[a] = gap/numTrials;
#else
#define LOAD_END(a) gap = timestamp() - start; buf[a] = gap/numTrials;
#endif


//#define MOV(a)     "movq $"#a", 0%0 \n\t"
#define MOV(a)		"movq "#a"%0, %%rax \n\t"
#define MOV2(a)		MOV(a) MOV(a+1)
#define MOV3(a)		MOV(a) MOV2(a+1)
#define MOV4(a)		MOV(a) MOV3(a+1)
#define MOV5(a)		MOV(a) MOV4(a+1)
#define MOV6(a)		MOV(a) MOV5(a+1)
#define MOV7(a)		MOV(a) MOV6(a+1)
#define MOV8(a)		MOV(a) MOV7(a+1)
#define MOV9(a)		MOV(a) MOV8(a+1)
#define MOV10(a)	MOV5(a) MOV5(a+5)
#define MOV20(a)	MOV10(a) MOV10(a+10)
#define MOV30(a)	MOV10(a) MOV20(a+10)
#define MOV40(a)	MOV20(a) MOV20(a+20)
#define MOV50(a)	MOV20(a) MOV20(a+20) MOV10(a+40)
#define MOV60(a)	MOV50(a) MOV10(a+50)
#define MOV70(a)	MOV50(a) MOV20(a+50)
#define MOV80(a)	MOV50(a) MOV30(a+50)

#define MFENCE		ASM_PREFIX "mfence\n\t" ASM_SUFFIX

#define NOP			"nop\n\t"
#define NOP10		NOP NOP NOP NOP NOP NOP NOP NOP NOP NOP
#define NOP50		NOP10 NOP10 NOP10 NOP10 NOP10
#define NOP100		NOP50 NOP50
#define NOP500		NOP100 NOP100 NOP100 NOP100 NOP100
int load_buffer(int iter);

#endif /* __LOAD_BUFFER__ */
