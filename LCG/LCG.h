#ifndef LCG_H
#define LCG_H


class LCG {
public:
    explicit LCG(unsigned int seed, unsigned int a = 48271, unsigned int c = 0,
                 unsigned int m = 2147483647);

    char next();

private:
    unsigned int seed;
    unsigned int a, c, m;
};


#endif
