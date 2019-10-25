#include "fixedint.h"
#include "fe.h"


/*
    helper functions
*/
static u64 load_3(const u8 *in) {
    u64 result;

    result = (u64) in[0];
    result |= ((u64) in[1]) << 8;
    result |= ((u64) in[2]) << 16;

    return result;
}

static u64 load_4(const u8 *in) {
    u64 result;

    result = (u64) in[0];
    result |= ((u64) in[1]) << 8;
    result |= ((u64) in[2]) << 16;
    result |= ((u64) in[3]) << 24;
    
    return result;
}



/*
    h = 0
*/

void fe_0(fe h) {
    h[0] = 0;
    h[1] = 0;
    h[2] = 0;
    h[3] = 0;
    h[4] = 0;
    h[5] = 0;
    h[6] = 0;
    h[7] = 0;
    h[8] = 0;
    h[9] = 0;
}



/*
    h = 1
*/

void fe_1(fe h) {
    h[0] = 1;
    h[1] = 0;
    h[2] = 0;
    h[3] = 0;
    h[4] = 0;
    h[5] = 0;
    h[6] = 0;
    h[7] = 0;
    h[8] = 0;
    h[9] = 0;
}



/*
    h = f + g
    Can overlap h with f or g.

    Preconditions:
       |f| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
       |g| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.

    Postconditions:
       |h| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/

void fe_add(fe h, const fe f, const fe g) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t g0 = g[0];
    int32_t g1 = g[1];
    int32_t g2 = g[2];
    int32_t g3 = g[3];
    int32_t g4 = g[4];
    int32_t g5 = g[5];
    int32_t g6 = g[6];
    int32_t g7 = g[7];
    int32_t g8 = g[8];
    int32_t g9 = g[9];
    int32_t h0 = f0 + g0;
    int32_t h1 = f1 + g1;
    int32_t h2 = f2 + g2;
    int32_t h3 = f3 + g3;
    int32_t h4 = f4 + g4;
    int32_t h5 = f5 + g5;
    int32_t h6 = f6 + g6;
    int32_t h7 = f7 + g7;
    int32_t h8 = f8 + g8;
    int32_t h9 = f9 + g9;
    
    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    h[4] = h4;
    h[5] = h5;
    h[6] = h6;
    h[7] = h7;
    h[8] = h8;
    h[9] = h9;
}



/*
    Replace (f,g) with (g,g) if b == 1;
    replace (f,g) with (f,g) if b == 0.

    Preconditions: b in {0,1}.
*/

void fe_cmov(fe f, const fe g, unsigned int b) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t g0 = g[0];
    int32_t g1 = g[1];
    int32_t g2 = g[2];
    int32_t g3 = g[3];
    int32_t g4 = g[4];
    int32_t g5 = g[5];
    int32_t g6 = g[6];
    int32_t g7 = g[7];
    int32_t g8 = g[8];
    int32_t g9 = g[9];
    int32_t x0 = f0 ^ g0;
    int32_t x1 = f1 ^ g1;
    int32_t x2 = f2 ^ g2;
    int32_t x3 = f3 ^ g3;
    int32_t x4 = f4 ^ g4;
    int32_t x5 = f5 ^ g5;
    int32_t x6 = f6 ^ g6;
    int32_t x7 = f7 ^ g7;
    int32_t x8 = f8 ^ g8;
    int32_t x9 = f9 ^ g9;

    b = (unsigned int) (- (int) b); /* silence warning */
    x0 &= b;
    x1 &= b;
    x2 &= b;
    x3 &= b;
    x4 &= b;
    x5 &= b;
    x6 &= b;
    x7 &= b;
    x8 &= b;
    x9 &= b;
    
    f[0] = f0 ^ x0;
    f[1] = f1 ^ x1;
    f[2] = f2 ^ x2;
    f[3] = f3 ^ x3;
    f[4] = f4 ^ x4;
    f[5] = f5 ^ x5;
    f[6] = f6 ^ x6;
    f[7] = f7 ^ x7;
    f[8] = f8 ^ x8;
    f[9] = f9 ^ x9;
}

/*
    Replace (f,g) with (g,f) if b == 1;
    replace (f,g) with (f,g) if b == 0.

    Preconditions: b in {0,1}.
*/

void fe_cswap(fe f,fe g,unsigned int b) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t g0 = g[0];
    int32_t g1 = g[1];
    int32_t g2 = g[2];
    int32_t g3 = g[3];
    int32_t g4 = g[4];
    int32_t g5 = g[5];
    int32_t g6 = g[6];
    int32_t g7 = g[7];
    int32_t g8 = g[8];
    int32_t g9 = g[9];
    int32_t x0 = f0 ^ g0;
    int32_t x1 = f1 ^ g1;
    int32_t x2 = f2 ^ g2;
    int32_t x3 = f3 ^ g3;
    int32_t x4 = f4 ^ g4;
    int32_t x5 = f5 ^ g5;
    int32_t x6 = f6 ^ g6;
    int32_t x7 = f7 ^ g7;
    int32_t x8 = f8 ^ g8;
    int32_t x9 = f9 ^ g9;
    b = (unsigned int) (- (int) b); /* silence warning */
    x0 &= b;
    x1 &= b;
    x2 &= b;
    x3 &= b;
    x4 &= b;
    x5 &= b;
    x6 &= b;
    x7 &= b;
    x8 &= b;
    x9 &= b;
    f[0] = f0 ^ x0;
    f[1] = f1 ^ x1;
    f[2] = f2 ^ x2;
    f[3] = f3 ^ x3;
    f[4] = f4 ^ x4;
    f[5] = f5 ^ x5;
    f[6] = f6 ^ x6;
    f[7] = f7 ^ x7;
    f[8] = f8 ^ x8;
    f[9] = f9 ^ x9;
    g[0] = g0 ^ x0;
    g[1] = g1 ^ x1;
    g[2] = g2 ^ x2;
    g[3] = g3 ^ x3;
    g[4] = g4 ^ x4;
    g[5] = g5 ^ x5;
    g[6] = g6 ^ x6;
    g[7] = g7 ^ x7;
    g[8] = g8 ^ x8;
    g[9] = g9 ^ x9;
}



/*
    h = f
*/

void fe_copy(fe h, const fe f) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    
    h[0] = f0;
    h[1] = f1;
    h[2] = f2;
    h[3] = f3;
    h[4] = f4;
    h[5] = f5;
    h[6] = f6;
    h[7] = f7;
    h[8] = f8;
    h[9] = f9;
}



/*
    Ignores top bit of h.
*/

void fe_frombytes(fe h, const u8 *s) {
    i64 h0 = load_4(s);
    i64 h1 = load_3(s + 4) << 6;
    i64 h2 = load_3(s + 7) << 5;
    i64 h3 = load_3(s + 10) << 3;
    i64 h4 = load_3(s + 13) << 2;
    i64 h5 = load_4(s + 16);
    i64 h6 = load_3(s + 20) << 7;
    i64 h7 = load_3(s + 23) << 5;
    i64 h8 = load_3(s + 26) << 4;
    i64 h9 = (load_3(s + 29) & 8388607) << 2;
    i64 carry0;
    i64 carry1;
    i64 carry2;
    i64 carry3;
    i64 carry4;
    i64 carry5;
    i64 carry6;
    i64 carry7;
    i64 carry8;
    i64 carry9;

    carry9 = (h9 + (i64) (1 << 24)) >> 25;
    h0 += carry9 * 19;
    h9 -= carry9 << 25;
    carry1 = (h1 + (i64) (1 << 24)) >> 25;
    h2 += carry1;
    h1 -= carry1 << 25;
    carry3 = (h3 + (i64) (1 << 24)) >> 25;
    h4 += carry3;
    h3 -= carry3 << 25;
    carry5 = (h5 + (i64) (1 << 24)) >> 25;
    h6 += carry5;
    h5 -= carry5 << 25;
    carry7 = (h7 + (i64) (1 << 24)) >> 25;
    h8 += carry7;
    h7 -= carry7 << 25;
    carry0 = (h0 + (i64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    carry2 = (h2 + (i64) (1 << 25)) >> 26;
    h3 += carry2;
    h2 -= carry2 << 26;
    carry4 = (h4 + (i64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry6 = (h6 + (i64) (1 << 25)) >> 26;
    h7 += carry6;
    h6 -= carry6 << 26;
    carry8 = (h8 + (i64) (1 << 25)) >> 26;
    h9 += carry8;
    h8 -= carry8 << 26;

    h[0] = (int32_t) h0;
    h[1] = (int32_t) h1;
    h[2] = (int32_t) h2;
    h[3] = (int32_t) h3;
    h[4] = (int32_t) h4;
    h[5] = (int32_t) h5;
    h[6] = (int32_t) h6;
    h[7] = (int32_t) h7;
    h[8] = (int32_t) h8;
    h[9] = (int32_t) h9;
}



void fe_invert(fe out, const fe z) {
    fe t0;
    fe t1;
    fe t2;
    fe t3;
    int i;

    fe_sq(t0, z);

    for (i = 1; i < 1; ++i) {
        fe_sq(t0, t0);
    }

    fe_sq(t1, t0);

    for (i = 1; i < 2; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, z, t1);
    fe_mul(t0, t0, t1);
    fe_sq(t2, t0);

    for (i = 1; i < 1; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t1, t2);
    fe_sq(t2, t1);

    for (i = 1; i < 5; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t2, t1);

    for (i = 1; i < 10; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t2, t2, t1);
    fe_sq(t3, t2);

    for (i = 1; i < 20; ++i) {
        fe_sq(t3, t3);
    }

    fe_mul(t2, t3, t2);
    fe_sq(t2, t2);

    for (i = 1; i < 10; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t2, t1);

    for (i = 1; i < 50; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t2, t2, t1);
    fe_sq(t3, t2);

    for (i = 1; i < 100; ++i) {
        fe_sq(t3, t3);
    }

    fe_mul(t2, t3, t2);
    fe_sq(t2, t2);

    for (i = 1; i < 50; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t1, t1);

    for (i = 1; i < 5; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(out, t1, t0);
}



/*
    return 1 if f is in {1,3,5,...,q-2}
    return 0 if f is in {0,2,4,...,q-1}

    Preconditions:
       |f| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/

int fe_isnegative(const fe f) {
    u8 s[32];

    fe_tobytes(s, f);
    
    return s[0] & 1;
}



/*
    return 1 if f == 0
    return 0 if f != 0

    Preconditions:
       |f| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/
// FUCK!!!!
// #define F(i) r |= s[i]

int fe_isnonzero(const fe f) {
    u8 s[32];
    u8 r;

    fe_tobytes(s, f);

    r = s[0];
    F(1);
    F(2);
    F(3);
    F(4);
    F(5);
    F(6);
    F(7);
    F(8);
    F(9);
    F(10);
    F(11);
    F(12);
    F(13);
    F(14);
    F(15);
    F(16);
    F(17);
    F(18);
    F(19);
    F(20);
    F(21);
    F(22);
    F(23);
    F(24);
    F(25);
    F(26);
    F(27);
    F(28);
    F(29);
    F(30);
    F(31);

    return r != 0;
}



/*
    h = f * g
    Can overlap h with f or g.

    Preconditions:
       |f| bounded by 1.65*2^26,1.65*2^25,1.65*2^26,1.65*2^25,etc.
       |g| bounded by 1.65*2^26,1.65*2^25,1.65*2^26,1.65*2^25,etc.

    Postconditions:
       |h| bounded by 1.01*2^25,1.01*2^24,1.01*2^25,1.01*2^24,etc.
    */

    /*
    Notes on implementation strategy:

    Using schoolbook multiplication.
    Karatsuba would save a little in some cost models.

    Most multiplications by 2 and 19 are 32-bit precomputations;
    cheaper than 64-bit postcomputations.

    There is one remaining multiplication by 19 in the carry chain;
    one *19 precomputation can be merged into this,
    but the resulting data flow is considerably less clean.

    There are 12 carries below.
    10 of them are 2-way parallelizable and vectorizable.
    Can get away with 11 carries, but then data flow is much deeper.

    With tighter constraints on inputs can squeeze carries into int32.
*/

void fe_mul(fe h, const fe f, const fe g) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t g0 = g[0];
    int32_t g1 = g[1];
    int32_t g2 = g[2];
    int32_t g3 = g[3];
    int32_t g4 = g[4];
    int32_t g5 = g[5];
    int32_t g6 = g[6];
    int32_t g7 = g[7];
    int32_t g8 = g[8];
    int32_t g9 = g[9];
    int32_t g1_19 = 19 * g1; /* 1.959375*2^29 */
    int32_t g2_19 = 19 * g2; /* 1.959375*2^30; still ok */
    int32_t g3_19 = 19 * g3;
    int32_t g4_19 = 19 * g4;
    int32_t g5_19 = 19 * g5;
    int32_t g6_19 = 19 * g6;
    int32_t g7_19 = 19 * g7;
    int32_t g8_19 = 19 * g8;
    int32_t g9_19 = 19 * g9;
    int32_t f1_2 = 2 * f1;
    int32_t f3_2 = 2 * f3;
    int32_t f5_2 = 2 * f5;
    int32_t f7_2 = 2 * f7;
    int32_t f9_2 = 2 * f9;
    i64 f0g0    = f0   * (i64) g0;
    i64 f0g1    = f0   * (i64) g1;
    i64 f0g2    = f0   * (i64) g2;
    i64 f0g3    = f0   * (i64) g3;
    i64 f0g4    = f0   * (i64) g4;
    i64 f0g5    = f0   * (i64) g5;
    i64 f0g6    = f0   * (i64) g6;
    i64 f0g7    = f0   * (i64) g7;
    i64 f0g8    = f0   * (i64) g8;
    i64 f0g9    = f0   * (i64) g9;
    i64 f1g0    = f1   * (i64) g0;
    i64 f1g1_2  = f1_2 * (i64) g1;
    i64 f1g2    = f1   * (i64) g2;
    i64 f1g3_2  = f1_2 * (i64) g3;
    i64 f1g4    = f1   * (i64) g4;
    i64 f1g5_2  = f1_2 * (i64) g5;
    i64 f1g6    = f1   * (i64) g6;
    i64 f1g7_2  = f1_2 * (i64) g7;
    i64 f1g8    = f1   * (i64) g8;
    i64 f1g9_38 = f1_2 * (i64) g9_19;
    i64 f2g0    = f2   * (i64) g0;
    i64 f2g1    = f2   * (i64) g1;
    i64 f2g2    = f2   * (i64) g2;
    i64 f2g3    = f2   * (i64) g3;
    i64 f2g4    = f2   * (i64) g4;
    i64 f2g5    = f2   * (i64) g5;
    i64 f2g6    = f2   * (i64) g6;
    i64 f2g7    = f2   * (i64) g7;
    i64 f2g8_19 = f2   * (i64) g8_19;
    i64 f2g9_19 = f2   * (i64) g9_19;
    i64 f3g0    = f3   * (i64) g0;
    i64 f3g1_2  = f3_2 * (i64) g1;
    i64 f3g2    = f3   * (i64) g2;
    i64 f3g3_2  = f3_2 * (i64) g3;
    i64 f3g4    = f3   * (i64) g4;
    i64 f3g5_2  = f3_2 * (i64) g5;
    i64 f3g6    = f3   * (i64) g6;
    i64 f3g7_38 = f3_2 * (i64) g7_19;
    i64 f3g8_19 = f3   * (i64) g8_19;
    i64 f3g9_38 = f3_2 * (i64) g9_19;
    i64 f4g0    = f4   * (i64) g0;
    i64 f4g1    = f4   * (i64) g1;
    i64 f4g2    = f4   * (i64) g2;
    i64 f4g3    = f4   * (i64) g3;
    i64 f4g4    = f4   * (i64) g4;
    i64 f4g5    = f4   * (i64) g5;
    i64 f4g6_19 = f4   * (i64) g6_19;
    i64 f4g7_19 = f4   * (i64) g7_19;
    i64 f4g8_19 = f4   * (i64) g8_19;
    i64 f4g9_19 = f4   * (i64) g9_19;
    i64 f5g0    = f5   * (i64) g0;
    i64 f5g1_2  = f5_2 * (i64) g1;
    i64 f5g2    = f5   * (i64) g2;
    i64 f5g3_2  = f5_2 * (i64) g3;
    i64 f5g4    = f5   * (i64) g4;
    i64 f5g5_38 = f5_2 * (i64) g5_19;
    i64 f5g6_19 = f5   * (i64) g6_19;
    i64 f5g7_38 = f5_2 * (i64) g7_19;
    i64 f5g8_19 = f5   * (i64) g8_19;
    i64 f5g9_38 = f5_2 * (i64) g9_19;
    i64 f6g0    = f6   * (i64) g0;
    i64 f6g1    = f6   * (i64) g1;
    i64 f6g2    = f6   * (i64) g2;
    i64 f6g3    = f6   * (i64) g3;
    i64 f6g4_19 = f6   * (i64) g4_19;
    i64 f6g5_19 = f6   * (i64) g5_19;
    i64 f6g6_19 = f6   * (i64) g6_19;
    i64 f6g7_19 = f6   * (i64) g7_19;
    i64 f6g8_19 = f6   * (i64) g8_19;
    i64 f6g9_19 = f6   * (i64) g9_19;
    i64 f7g0    = f7   * (i64) g0;
    i64 f7g1_2  = f7_2 * (i64) g1;
    i64 f7g2    = f7   * (i64) g2;
    i64 f7g3_38 = f7_2 * (i64) g3_19;
    i64 f7g4_19 = f7   * (i64) g4_19;
    i64 f7g5_38 = f7_2 * (i64) g5_19;
    i64 f7g6_19 = f7   * (i64) g6_19;
    i64 f7g7_38 = f7_2 * (i64) g7_19;
    i64 f7g8_19 = f7   * (i64) g8_19;
    i64 f7g9_38 = f7_2 * (i64) g9_19;
    i64 f8g0    = f8   * (i64) g0;
    i64 f8g1    = f8   * (i64) g1;
    i64 f8g2_19 = f8   * (i64) g2_19;
    i64 f8g3_19 = f8   * (i64) g3_19;
    i64 f8g4_19 = f8   * (i64) g4_19;
    i64 f8g5_19 = f8   * (i64) g5_19;
    i64 f8g6_19 = f8   * (i64) g6_19;
    i64 f8g7_19 = f8   * (i64) g7_19;
    i64 f8g8_19 = f8   * (i64) g8_19;
    i64 f8g9_19 = f8   * (i64) g9_19;
    i64 f9g0    = f9   * (i64) g0;
    i64 f9g1_38 = f9_2 * (i64) g1_19;
    i64 f9g2_19 = f9   * (i64) g2_19;
    i64 f9g3_38 = f9_2 * (i64) g3_19;
    i64 f9g4_19 = f9   * (i64) g4_19;
    i64 f9g5_38 = f9_2 * (i64) g5_19;
    i64 f9g6_19 = f9   * (i64) g6_19;
    i64 f9g7_38 = f9_2 * (i64) g7_19;
    i64 f9g8_19 = f9   * (i64) g8_19;
    i64 f9g9_38 = f9_2 * (i64) g9_19;
    i64 h0 = f0g0 + f1g9_38 + f2g8_19 + f3g7_38 + f4g6_19 + f5g5_38 + f6g4_19 + f7g3_38 + f8g2_19 + f9g1_38;
    i64 h1 = f0g1 + f1g0   + f2g9_19 + f3g8_19 + f4g7_19 + f5g6_19 + f6g5_19 + f7g4_19 + f8g3_19 + f9g2_19;
    i64 h2 = f0g2 + f1g1_2 + f2g0   + f3g9_38 + f4g8_19 + f5g7_38 + f6g6_19 + f7g5_38 + f8g4_19 + f9g3_38;
    i64 h3 = f0g3 + f1g2   + f2g1   + f3g0   + f4g9_19 + f5g8_19 + f6g7_19 + f7g6_19 + f8g5_19 + f9g4_19;
    i64 h4 = f0g4 + f1g3_2 + f2g2   + f3g1_2 + f4g0   + f5g9_38 + f6g8_19 + f7g7_38 + f8g6_19 + f9g5_38;
    i64 h5 = f0g5 + f1g4   + f2g3   + f3g2   + f4g1   + f5g0   + f6g9_19 + f7g8_19 + f8g7_19 + f9g6_19;
    i64 h6 = f0g6 + f1g5_2 + f2g4   + f3g3_2 + f4g2   + f5g1_2 + f6g0   + f7g9_38 + f8g8_19 + f9g7_38;
    i64 h7 = f0g7 + f1g6   + f2g5   + f3g4   + f4g3   + f5g2   + f6g1   + f7g0   + f8g9_19 + f9g8_19;
    i64 h8 = f0g8 + f1g7_2 + f2g6   + f3g5_2 + f4g4   + f5g3_2 + f6g2   + f7g1_2 + f8g0   + f9g9_38;
    i64 h9 = f0g9 + f1g8   + f2g7   + f3g6   + f4g5   + f5g4   + f6g3   + f7g2   + f8g1   + f9g0   ;
    i64 carry0;
    i64 carry1;
    i64 carry2;
    i64 carry3;
    i64 carry4;
    i64 carry5;
    i64 carry6;
    i64 carry7;
    i64 carry8;
    i64 carry9;

    carry0 = (h0 + (i64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    carry4 = (h4 + (i64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;

    carry1 = (h1 + (i64) (1 << 24)) >> 25;
    h2 += carry1;
    h1 -= carry1 << 25;
    carry5 = (h5 + (i64) (1 << 24)) >> 25;
    h6 += carry5;
    h5 -= carry5 << 25;

    carry2 = (h2 + (i64) (1 << 25)) >> 26;
    h3 += carry2;
    h2 -= carry2 << 26;
    carry6 = (h6 + (i64) (1 << 25)) >> 26;
    h7 += carry6;
    h6 -= carry6 << 26;

    carry3 = (h3 + (i64) (1 << 24)) >> 25;
    h4 += carry3;
    h3 -= carry3 << 25;
    carry7 = (h7 + (i64) (1 << 24)) >> 25;
    h8 += carry7;
    h7 -= carry7 << 25;

    carry4 = (h4 + (i64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry8 = (h8 + (i64) (1 << 25)) >> 26;
    h9 += carry8;
    h8 -= carry8 << 26;

    carry9 = (h9 + (i64) (1 << 24)) >> 25;
    h0 += carry9 * 19;
    h9 -= carry9 << 25;

    carry0 = (h0 + (i64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;

    h[0] = (int32_t) h0;
    h[1] = (int32_t) h1;
    h[2] = (int32_t) h2;
    h[3] = (int32_t) h3;
    h[4] = (int32_t) h4;
    h[5] = (int32_t) h5;
    h[6] = (int32_t) h6;
    h[7] = (int32_t) h7;
    h[8] = (int32_t) h8;
    h[9] = (int32_t) h9;
}


/*
h = f * 121666
Can overlap h with f.

Preconditions:
   |f| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.

Postconditions:
   |h| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
*/

void fe_mul121666(fe h, fe f) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    i64 h0 = f0 * (i64) 121666;
    i64 h1 = f1 * (i64) 121666;
    i64 h2 = f2 * (i64) 121666;
    i64 h3 = f3 * (i64) 121666;
    i64 h4 = f4 * (i64) 121666;
    i64 h5 = f5 * (i64) 121666;
    i64 h6 = f6 * (i64) 121666;
    i64 h7 = f7 * (i64) 121666;
    i64 h8 = f8 * (i64) 121666;
    i64 h9 = f9 * (i64) 121666;
    i64 carry0;
    i64 carry1;
    i64 carry2;
    i64 carry3;
    i64 carry4;
    i64 carry5;
    i64 carry6;
    i64 carry7;
    i64 carry8;
    i64 carry9;

    carry9 = (h9 + (i64) (1<<24)) >> 25; h0 += carry9 * 19; h9 -= carry9 << 25;
    carry1 = (h1 + (i64) (1<<24)) >> 25; h2 += carry1; h1 -= carry1 << 25;
    carry3 = (h3 + (i64) (1<<24)) >> 25; h4 += carry3; h3 -= carry3 << 25;
    carry5 = (h5 + (i64) (1<<24)) >> 25; h6 += carry5; h5 -= carry5 << 25;
    carry7 = (h7 + (i64) (1<<24)) >> 25; h8 += carry7; h7 -= carry7 << 25;

    carry0 = (h0 + (i64) (1<<25)) >> 26; h1 += carry0; h0 -= carry0 << 26;
    carry2 = (h2 + (i64) (1<<25)) >> 26; h3 += carry2; h2 -= carry2 << 26;
    carry4 = (h4 + (i64) (1<<25)) >> 26; h5 += carry4; h4 -= carry4 << 26;
    carry6 = (h6 + (i64) (1<<25)) >> 26; h7 += carry6; h6 -= carry6 << 26;
    carry8 = (h8 + (i64) (1<<25)) >> 26; h9 += carry8; h8 -= carry8 << 26;

    h[0] = (int32_t) h0;
    h[1] = (int32_t) h1;
    h[2] = (int32_t) h2;
    h[3] = (int32_t) h3;
    h[4] = (int32_t) h4;
    h[5] = (int32_t) h5;
    h[6] = (int32_t) h6;
    h[7] = (int32_t) h7;
    h[8] = (int32_t) h8;
    h[9] = (int32_t) h9;
}


/*
h = -f

Preconditions:
   |f| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.

Postconditions:
   |h| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
*/

void fe_neg(fe h, const fe f) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t h0 = -f0;
    int32_t h1 = -f1;
    int32_t h2 = -f2;
    int32_t h3 = -f3;
    int32_t h4 = -f4;
    int32_t h5 = -f5;
    int32_t h6 = -f6;
    int32_t h7 = -f7;
    int32_t h8 = -f8;
    int32_t h9 = -f9;

    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    h[4] = h4;
    h[5] = h5;
    h[6] = h6;
    h[7] = h7;
    h[8] = h8;
    h[9] = h9;
}


void fe_pow22523(fe out, const fe z) {
    fe t0;
    fe t1;
    fe t2;
    int i;
    fe_sq(t0, z);

    for (i = 1; i < 1; ++i) {
        fe_sq(t0, t0);
    }

    fe_sq(t1, t0);

    for (i = 1; i < 2; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, z, t1);
    fe_mul(t0, t0, t1);
    fe_sq(t0, t0);

    for (i = 1; i < 1; ++i) {
        fe_sq(t0, t0);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t1, t0);

    for (i = 1; i < 5; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t1, t0);

    for (i = 1; i < 10; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, t1, t0);
    fe_sq(t2, t1);

    for (i = 1; i < 20; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t1, t1);

    for (i = 1; i < 10; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t1, t0);

    for (i = 1; i < 50; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t1, t1, t0);
    fe_sq(t2, t1);

    for (i = 1; i < 100; ++i) {
        fe_sq(t2, t2);
    }

    fe_mul(t1, t2, t1);
    fe_sq(t1, t1);

    for (i = 1; i < 50; ++i) {
        fe_sq(t1, t1);
    }

    fe_mul(t0, t1, t0);
    fe_sq(t0, t0);

    for (i = 1; i < 2; ++i) {
        fe_sq(t0, t0);
    }

    fe_mul(out, t0, z);
    return;
}


/*
h = f * f
Can overlap h with f.

Preconditions:
   |f| bounded by 1.65*2^26,1.65*2^25,1.65*2^26,1.65*2^25,etc.

Postconditions:
   |h| bounded by 1.01*2^25,1.01*2^24,1.01*2^25,1.01*2^24,etc.
*/

/*
See fe_mul.c for discussion of implementation strategy.
*/

void fe_sq(fe h, const fe f) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t f0_2 = 2 * f0;
    int32_t f1_2 = 2 * f1;
    int32_t f2_2 = 2 * f2;
    int32_t f3_2 = 2 * f3;
    int32_t f4_2 = 2 * f4;
    int32_t f5_2 = 2 * f5;
    int32_t f6_2 = 2 * f6;
    int32_t f7_2 = 2 * f7;
    int32_t f5_38 = 38 * f5; /* 1.959375*2^30 */
    int32_t f6_19 = 19 * f6; /* 1.959375*2^30 */
    int32_t f7_38 = 38 * f7; /* 1.959375*2^30 */
    int32_t f8_19 = 19 * f8; /* 1.959375*2^30 */
    int32_t f9_38 = 38 * f9; /* 1.959375*2^30 */
    i64 f0f0    = f0   * (i64) f0;
    i64 f0f1_2  = f0_2 * (i64) f1;
    i64 f0f2_2  = f0_2 * (i64) f2;
    i64 f0f3_2  = f0_2 * (i64) f3;
    i64 f0f4_2  = f0_2 * (i64) f4;
    i64 f0f5_2  = f0_2 * (i64) f5;
    i64 f0f6_2  = f0_2 * (i64) f6;
    i64 f0f7_2  = f0_2 * (i64) f7;
    i64 f0f8_2  = f0_2 * (i64) f8;
    i64 f0f9_2  = f0_2 * (i64) f9;
    i64 f1f1_2  = f1_2 * (i64) f1;
    i64 f1f2_2  = f1_2 * (i64) f2;
    i64 f1f3_4  = f1_2 * (i64) f3_2;
    i64 f1f4_2  = f1_2 * (i64) f4;
    i64 f1f5_4  = f1_2 * (i64) f5_2;
    i64 f1f6_2  = f1_2 * (i64) f6;
    i64 f1f7_4  = f1_2 * (i64) f7_2;
    i64 f1f8_2  = f1_2 * (i64) f8;
    i64 f1f9_76 = f1_2 * (i64) f9_38;
    i64 f2f2    = f2   * (i64) f2;
    i64 f2f3_2  = f2_2 * (i64) f3;
    i64 f2f4_2  = f2_2 * (i64) f4;
    i64 f2f5_2  = f2_2 * (i64) f5;
    i64 f2f6_2  = f2_2 * (i64) f6;
    i64 f2f7_2  = f2_2 * (i64) f7;
    i64 f2f8_38 = f2_2 * (i64) f8_19;
    i64 f2f9_38 = f2   * (i64) f9_38;
    i64 f3f3_2  = f3_2 * (i64) f3;
    i64 f3f4_2  = f3_2 * (i64) f4;
    i64 f3f5_4  = f3_2 * (i64) f5_2;
    i64 f3f6_2  = f3_2 * (i64) f6;
    i64 f3f7_76 = f3_2 * (i64) f7_38;
    i64 f3f8_38 = f3_2 * (i64) f8_19;
    i64 f3f9_76 = f3_2 * (i64) f9_38;
    i64 f4f4    = f4   * (i64) f4;
    i64 f4f5_2  = f4_2 * (i64) f5;
    i64 f4f6_38 = f4_2 * (i64) f6_19;
    i64 f4f7_38 = f4   * (i64) f7_38;
    i64 f4f8_38 = f4_2 * (i64) f8_19;
    i64 f4f9_38 = f4   * (i64) f9_38;
    i64 f5f5_38 = f5   * (i64) f5_38;
    i64 f5f6_38 = f5_2 * (i64) f6_19;
    i64 f5f7_76 = f5_2 * (i64) f7_38;
    i64 f5f8_38 = f5_2 * (i64) f8_19;
    i64 f5f9_76 = f5_2 * (i64) f9_38;
    i64 f6f6_19 = f6   * (i64) f6_19;
    i64 f6f7_38 = f6   * (i64) f7_38;
    i64 f6f8_38 = f6_2 * (i64) f8_19;
    i64 f6f9_38 = f6   * (i64) f9_38;
    i64 f7f7_38 = f7   * (i64) f7_38;
    i64 f7f8_38 = f7_2 * (i64) f8_19;
    i64 f7f9_76 = f7_2 * (i64) f9_38;
    i64 f8f8_19 = f8   * (i64) f8_19;
    i64 f8f9_38 = f8   * (i64) f9_38;
    i64 f9f9_38 = f9   * (i64) f9_38;
    i64 h0 = f0f0  + f1f9_76 + f2f8_38 + f3f7_76 + f4f6_38 + f5f5_38;
    i64 h1 = f0f1_2 + f2f9_38 + f3f8_38 + f4f7_38 + f5f6_38;
    i64 h2 = f0f2_2 + f1f1_2 + f3f9_76 + f4f8_38 + f5f7_76 + f6f6_19;
    i64 h3 = f0f3_2 + f1f2_2 + f4f9_38 + f5f8_38 + f6f7_38;
    i64 h4 = f0f4_2 + f1f3_4 + f2f2   + f5f9_76 + f6f8_38 + f7f7_38;
    i64 h5 = f0f5_2 + f1f4_2 + f2f3_2 + f6f9_38 + f7f8_38;
    i64 h6 = f0f6_2 + f1f5_4 + f2f4_2 + f3f3_2 + f7f9_76 + f8f8_19;
    i64 h7 = f0f7_2 + f1f6_2 + f2f5_2 + f3f4_2 + f8f9_38;
    i64 h8 = f0f8_2 + f1f7_4 + f2f6_2 + f3f5_4 + f4f4   + f9f9_38;
    i64 h9 = f0f9_2 + f1f8_2 + f2f7_2 + f3f6_2 + f4f5_2;
    i64 carry0;
    i64 carry1;
    i64 carry2;
    i64 carry3;
    i64 carry4;
    i64 carry5;
    i64 carry6;
    i64 carry7;
    i64 carry8;
    i64 carry9;
    carry0 = (h0 + (i64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    carry4 = (h4 + (i64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry1 = (h1 + (i64) (1 << 24)) >> 25;
    h2 += carry1;
    h1 -= carry1 << 25;
    carry5 = (h5 + (i64) (1 << 24)) >> 25;
    h6 += carry5;
    h5 -= carry5 << 25;
    carry2 = (h2 + (i64) (1 << 25)) >> 26;
    h3 += carry2;
    h2 -= carry2 << 26;
    carry6 = (h6 + (i64) (1 << 25)) >> 26;
    h7 += carry6;
    h6 -= carry6 << 26;
    carry3 = (h3 + (i64) (1 << 24)) >> 25;
    h4 += carry3;
    h3 -= carry3 << 25;
    carry7 = (h7 + (i64) (1 << 24)) >> 25;
    h8 += carry7;
    h7 -= carry7 << 25;
    carry4 = (h4 + (i64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry8 = (h8 + (i64) (1 << 25)) >> 26;
    h9 += carry8;
    h8 -= carry8 << 26;
    carry9 = (h9 + (i64) (1 << 24)) >> 25;
    h0 += carry9 * 19;
    h9 -= carry9 << 25;
    carry0 = (h0 + (i64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    h[0] = (int32_t) h0;
    h[1] = (int32_t) h1;
    h[2] = (int32_t) h2;
    h[3] = (int32_t) h3;
    h[4] = (int32_t) h4;
    h[5] = (int32_t) h5;
    h[6] = (int32_t) h6;
    h[7] = (int32_t) h7;
    h[8] = (int32_t) h8;
    h[9] = (int32_t) h9;
}


/*
h = 2 * f * f
Can overlap h with f.

Preconditions:
   |f| bounded by 1.65*2^26,1.65*2^25,1.65*2^26,1.65*2^25,etc.

Postconditions:
   |h| bounded by 1.01*2^25,1.01*2^24,1.01*2^25,1.01*2^24,etc.
*/

/*
See fe_mul.c for discussion of implementation strategy.
*/

void fe_sq2(fe h, const fe f) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t f0_2 = 2 * f0;
    int32_t f1_2 = 2 * f1;
    int32_t f2_2 = 2 * f2;
    int32_t f3_2 = 2 * f3;
    int32_t f4_2 = 2 * f4;
    int32_t f5_2 = 2 * f5;
    int32_t f6_2 = 2 * f6;
    int32_t f7_2 = 2 * f7;
    int32_t f5_38 = 38 * f5; /* 1.959375*2^30 */
    int32_t f6_19 = 19 * f6; /* 1.959375*2^30 */
    int32_t f7_38 = 38 * f7; /* 1.959375*2^30 */
    int32_t f8_19 = 19 * f8; /* 1.959375*2^30 */
    int32_t f9_38 = 38 * f9; /* 1.959375*2^30 */
    i64 f0f0    = f0   * (i64) f0;
    i64 f0f1_2  = f0_2 * (i64) f1;
    i64 f0f2_2  = f0_2 * (i64) f2;
    i64 f0f3_2  = f0_2 * (i64) f3;
    i64 f0f4_2  = f0_2 * (i64) f4;
    i64 f0f5_2  = f0_2 * (i64) f5;
    i64 f0f6_2  = f0_2 * (i64) f6;
    i64 f0f7_2  = f0_2 * (i64) f7;
    i64 f0f8_2  = f0_2 * (i64) f8;
    i64 f0f9_2  = f0_2 * (i64) f9;
    i64 f1f1_2  = f1_2 * (i64) f1;
    i64 f1f2_2  = f1_2 * (i64) f2;
    i64 f1f3_4  = f1_2 * (i64) f3_2;
    i64 f1f4_2  = f1_2 * (i64) f4;
    i64 f1f5_4  = f1_2 * (i64) f5_2;
    i64 f1f6_2  = f1_2 * (i64) f6;
    i64 f1f7_4  = f1_2 * (i64) f7_2;
    i64 f1f8_2  = f1_2 * (i64) f8;
    i64 f1f9_76 = f1_2 * (i64) f9_38;
    i64 f2f2    = f2   * (i64) f2;
    i64 f2f3_2  = f2_2 * (i64) f3;
    i64 f2f4_2  = f2_2 * (i64) f4;
    i64 f2f5_2  = f2_2 * (i64) f5;
    i64 f2f6_2  = f2_2 * (i64) f6;
    i64 f2f7_2  = f2_2 * (i64) f7;
    i64 f2f8_38 = f2_2 * (i64) f8_19;
    i64 f2f9_38 = f2   * (i64) f9_38;
    i64 f3f3_2  = f3_2 * (i64) f3;
    i64 f3f4_2  = f3_2 * (i64) f4;
    i64 f3f5_4  = f3_2 * (i64) f5_2;
    i64 f3f6_2  = f3_2 * (i64) f6;
    i64 f3f7_76 = f3_2 * (i64) f7_38;
    i64 f3f8_38 = f3_2 * (i64) f8_19;
    i64 f3f9_76 = f3_2 * (i64) f9_38;
    i64 f4f4    = f4   * (i64) f4;
    i64 f4f5_2  = f4_2 * (i64) f5;
    i64 f4f6_38 = f4_2 * (i64) f6_19;
    i64 f4f7_38 = f4   * (i64) f7_38;
    i64 f4f8_38 = f4_2 * (i64) f8_19;
    i64 f4f9_38 = f4   * (i64) f9_38;
    i64 f5f5_38 = f5   * (i64) f5_38;
    i64 f5f6_38 = f5_2 * (i64) f6_19;
    i64 f5f7_76 = f5_2 * (i64) f7_38;
    i64 f5f8_38 = f5_2 * (i64) f8_19;
    i64 f5f9_76 = f5_2 * (i64) f9_38;
    i64 f6f6_19 = f6   * (i64) f6_19;
    i64 f6f7_38 = f6   * (i64) f7_38;
    i64 f6f8_38 = f6_2 * (i64) f8_19;
    i64 f6f9_38 = f6   * (i64) f9_38;
    i64 f7f7_38 = f7   * (i64) f7_38;
    i64 f7f8_38 = f7_2 * (i64) f8_19;
    i64 f7f9_76 = f7_2 * (i64) f9_38;
    i64 f8f8_19 = f8   * (i64) f8_19;
    i64 f8f9_38 = f8   * (i64) f9_38;
    i64 f9f9_38 = f9   * (i64) f9_38;
    i64 h0 = f0f0  + f1f9_76 + f2f8_38 + f3f7_76 + f4f6_38 + f5f5_38;
    i64 h1 = f0f1_2 + f2f9_38 + f3f8_38 + f4f7_38 + f5f6_38;
    i64 h2 = f0f2_2 + f1f1_2 + f3f9_76 + f4f8_38 + f5f7_76 + f6f6_19;
    i64 h3 = f0f3_2 + f1f2_2 + f4f9_38 + f5f8_38 + f6f7_38;
    i64 h4 = f0f4_2 + f1f3_4 + f2f2   + f5f9_76 + f6f8_38 + f7f7_38;
    i64 h5 = f0f5_2 + f1f4_2 + f2f3_2 + f6f9_38 + f7f8_38;
    i64 h6 = f0f6_2 + f1f5_4 + f2f4_2 + f3f3_2 + f7f9_76 + f8f8_19;
    i64 h7 = f0f7_2 + f1f6_2 + f2f5_2 + f3f4_2 + f8f9_38;
    i64 h8 = f0f8_2 + f1f7_4 + f2f6_2 + f3f5_4 + f4f4   + f9f9_38;
    i64 h9 = f0f9_2 + f1f8_2 + f2f7_2 + f3f6_2 + f4f5_2;
    i64 carry0;
    i64 carry1;
    i64 carry2;
    i64 carry3;
    i64 carry4;
    i64 carry5;
    i64 carry6;
    i64 carry7;
    i64 carry8;
    i64 carry9;
    h0 += h0;
    h1 += h1;
    h2 += h2;
    h3 += h3;
    h4 += h4;
    h5 += h5;
    h6 += h6;
    h7 += h7;
    h8 += h8;
    h9 += h9;
    carry0 = (h0 + (i64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    carry4 = (h4 + (i64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry1 = (h1 + (i64) (1 << 24)) >> 25;
    h2 += carry1;
    h1 -= carry1 << 25;
    carry5 = (h5 + (i64) (1 << 24)) >> 25;
    h6 += carry5;
    h5 -= carry5 << 25;
    carry2 = (h2 + (i64) (1 << 25)) >> 26;
    h3 += carry2;
    h2 -= carry2 << 26;
    carry6 = (h6 + (i64) (1 << 25)) >> 26;
    h7 += carry6;
    h6 -= carry6 << 26;
    carry3 = (h3 + (i64) (1 << 24)) >> 25;
    h4 += carry3;
    h3 -= carry3 << 25;
    carry7 = (h7 + (i64) (1 << 24)) >> 25;
    h8 += carry7;
    h7 -= carry7 << 25;
    carry4 = (h4 + (i64) (1 << 25)) >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry8 = (h8 + (i64) (1 << 25)) >> 26;
    h9 += carry8;
    h8 -= carry8 << 26;
    carry9 = (h9 + (i64) (1 << 24)) >> 25;
    h0 += carry9 * 19;
    h9 -= carry9 << 25;
    carry0 = (h0 + (i64) (1 << 25)) >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    h[0] = (int32_t) h0;
    h[1] = (int32_t) h1;
    h[2] = (int32_t) h2;
    h[3] = (int32_t) h3;
    h[4] = (int32_t) h4;
    h[5] = (int32_t) h5;
    h[6] = (int32_t) h6;
    h[7] = (int32_t) h7;
    h[8] = (int32_t) h8;
    h[9] = (int32_t) h9;
}


/*
h = f - g
Can overlap h with f or g.

Preconditions:
   |f| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.
   |g| bounded by 1.1*2^25,1.1*2^24,1.1*2^25,1.1*2^24,etc.

Postconditions:
   |h| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.
*/

void fe_sub(fe h, const fe f, const fe g) {
    int32_t f0 = f[0];
    int32_t f1 = f[1];
    int32_t f2 = f[2];
    int32_t f3 = f[3];
    int32_t f4 = f[4];
    int32_t f5 = f[5];
    int32_t f6 = f[6];
    int32_t f7 = f[7];
    int32_t f8 = f[8];
    int32_t f9 = f[9];
    int32_t g0 = g[0];
    int32_t g1 = g[1];
    int32_t g2 = g[2];
    int32_t g3 = g[3];
    int32_t g4 = g[4];
    int32_t g5 = g[5];
    int32_t g6 = g[6];
    int32_t g7 = g[7];
    int32_t g8 = g[8];
    int32_t g9 = g[9];
    int32_t h0 = f0 - g0;
    int32_t h1 = f1 - g1;
    int32_t h2 = f2 - g2;
    int32_t h3 = f3 - g3;
    int32_t h4 = f4 - g4;
    int32_t h5 = f5 - g5;
    int32_t h6 = f6 - g6;
    int32_t h7 = f7 - g7;
    int32_t h8 = f8 - g8;
    int32_t h9 = f9 - g9;

    h[0] = h0;
    h[1] = h1;
    h[2] = h2;
    h[3] = h3;
    h[4] = h4;
    h[5] = h5;
    h[6] = h6;
    h[7] = h7;
    h[8] = h8;
    h[9] = h9;
}



/*
Preconditions:
  |h| bounded by 1.1*2^26,1.1*2^25,1.1*2^26,1.1*2^25,etc.

Write p=2^255-19; q=floor(h/p).
Basic claim: q = floor(2^(-255)(h + 19 2^(-25)h9 + 2^(-1))).

Proof:
  Have |h|<=p so |q|<=1 so |19^2 2^(-255) q|<1/4.
  Also have |h-2^230 h9|<2^231 so |19 2^(-255)(h-2^230 h9)|<1/4.

  Write y=2^(-1)-19^2 2^(-255)q-19 2^(-255)(h-2^230 h9).
  Then 0<y<1.

  Write r=h-pq.
  Have 0<=r<=p-1=2^255-20.
  Thus 0<=r+19(2^-255)r<r+19(2^-255)2^255<=2^255-1.

  Write x=r+19(2^-255)r+y.
  Then 0<x<2^255 so floor(2^(-255)x) = 0 so floor(q+2^(-255)x) = q.

  Have q+2^(-255)x = 2^(-255)(h + 19 2^(-25) h9 + 2^(-1))
  so floor(2^(-255)(h + 19 2^(-25) h9 + 2^(-1))) = q.
*/

void fe_tobytes(u8 *s, const fe h) {
    int32_t h0 = h[0];
    int32_t h1 = h[1];
    int32_t h2 = h[2];
    int32_t h3 = h[3];
    int32_t h4 = h[4];
    int32_t h5 = h[5];
    int32_t h6 = h[6];
    int32_t h7 = h[7];
    int32_t h8 = h[8];
    int32_t h9 = h[9];
    int32_t q;
    int32_t carry0;
    int32_t carry1;
    int32_t carry2;
    int32_t carry3;
    int32_t carry4;
    int32_t carry5;
    int32_t carry6;
    int32_t carry7;
    int32_t carry8;
    int32_t carry9;
    q = (19 * h9 + (((int32_t) 1) << 24)) >> 25;
    q = (h0 + q) >> 26;
    q = (h1 + q) >> 25;
    q = (h2 + q) >> 26;
    q = (h3 + q) >> 25;
    q = (h4 + q) >> 26;
    q = (h5 + q) >> 25;
    q = (h6 + q) >> 26;
    q = (h7 + q) >> 25;
    q = (h8 + q) >> 26;
    q = (h9 + q) >> 25;
    /* Goal: Output h-(2^255-19)q, which is between 0 and 2^255-20. */
    h0 += 19 * q;
    /* Goal: Output h-2^255 q, which is between 0 and 2^255-20. */
    carry0 = h0 >> 26;
    h1 += carry0;
    h0 -= carry0 << 26;
    carry1 = h1 >> 25;
    h2 += carry1;
    h1 -= carry1 << 25;
    carry2 = h2 >> 26;
    h3 += carry2;
    h2 -= carry2 << 26;
    carry3 = h3 >> 25;
    h4 += carry3;
    h3 -= carry3 << 25;
    carry4 = h4 >> 26;
    h5 += carry4;
    h4 -= carry4 << 26;
    carry5 = h5 >> 25;
    h6 += carry5;
    h5 -= carry5 << 25;
    carry6 = h6 >> 26;
    h7 += carry6;
    h6 -= carry6 << 26;
    carry7 = h7 >> 25;
    h8 += carry7;
    h7 -= carry7 << 25;
    carry8 = h8 >> 26;
    h9 += carry8;
    h8 -= carry8 << 26;
    carry9 = h9 >> 25;
    h9 -= carry9 << 25;

    /* h10 = carry9 */
    /*
    Goal: Output h0+...+2^255 h10-2^255 q, which is between 0 and 2^255-20.
    Have h0+...+2^230 h9 between 0 and 2^255-1;
    evidently 2^255 h10-2^255 q = 0.
    Goal: Output h0+...+2^230 h9.
    */
    s[0] = (u8) (h0 >> 0);
    s[1] = (u8) (h0 >> 8);
    s[2] = (u8) (h0 >> 16);
    s[3] = (u8) ((h0 >> 24) | (h1 << 2));
    s[4] = (u8) (h1 >> 6);
    s[5] = (u8) (h1 >> 14);
    s[6] = (u8) ((h1 >> 22) | (h2 << 3));
    s[7] = (u8) (h2 >> 5);
    s[8] = (u8) (h2 >> 13);
    s[9] = (u8) ((h2 >> 21) | (h3 << 5));
    s[10] = (u8) (h3 >> 3);
    s[11] = (u8) (h3 >> 11);
    s[12] = (u8) ((h3 >> 19) | (h4 << 6));
    s[13] = (u8) (h4 >> 2);
    s[14] = (u8) (h4 >> 10);
    s[15] = (u8) (h4 >> 18);
    s[16] = (u8) (h5 >> 0);
    s[17] = (u8) (h5 >> 8);
    s[18] = (u8) (h5 >> 16);
    s[19] = (u8) ((h5 >> 24) | (h6 << 1));
    s[20] = (u8) (h6 >> 7);
    s[21] = (u8) (h6 >> 15);
    s[22] = (u8) ((h6 >> 23) | (h7 << 3));
    s[23] = (u8) (h7 >> 5);
    s[24] = (u8) (h7 >> 13);
    s[25] = (u8) ((h7 >> 21) | (h8 << 4));
    s[26] = (u8) (h8 >> 4);
    s[27] = (u8) (h8 >> 12);
    s[28] = (u8) ((h8 >> 20) | (h9 << 6));
    s[29] = (u8) (h9 >> 2);
    s[30] = (u8) (h9 >> 10);
    s[31] = (u8) (h9 >> 18);
}
