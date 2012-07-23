#ifndef _MORTONIZER_H_
#define _MORTONIZER_H_

// 3-Dimension
unsigned int mortonize(unsigned int x, unsigned int y, unsigned int z);
void demortonize(unsigned int morton_number, unsigned int &x, unsigned int &y, unsigned int &z);

// 2-Dimension
unsigned int mortonize(unsigned int x, unsigned int y);
void demortonize(unsigned int morton_number, unsigned int &x, unsigned int &y);


#endif // _MORTONIZER_H_
