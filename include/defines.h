#ifndef DEFINES_H
#define DEFINES_H

#define OPT_H 0x1
#define OPT_G 0x2
#define OPT_U 0x4
#define OPT_A 0x8
#define OPT_R 0x10
#define OPT_P 0x20

#define CHECK_FLAG(flag, opt) ((opt) & (flag))
#define CHECK_P(opt) CHECK_FLAG(OPT_P, (opt))
#define CHECK_R(opt) CHECK_FLAG(OPT_R, (opt))
#define CHECK_U(opt) CHECK_FLAG(OPT_U, (opt))
#define CHECK_A(opt) CHECK_FLAG(OPT_A, (opt))
#define CHECK_G(opt) CHECK_FLAG(OPT_G, (opt))
#define CHECK_H(opt) CHECK_FLAG(OPT_H, (opt))

#define STRTAB ".strtab"

#endif
