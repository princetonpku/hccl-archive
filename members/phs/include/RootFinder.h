#ifndef _ROOTFINDER_H_
#define _ROOTFINDER_H_

/* code example

class testFunction
{
public:
    double operator() (double x)
    {
        return cos(x)-x;
    }
};

RootFinder solver;
solver.setFunction(testFunction());
solver.findRoot(0.1)

*/

#include <functional>

class RootFinder
{
public:
    RootFinder();
    ~RootFinder();
    void setFunction(std::tr1::function<double(double)> f);
    double findRoot(double initialValue); // secant method
    void setMaxIteration(int n); // default 30
    void setTolerance(double tolerance); // default 1e-10
    int maxIteration();
    double tolerance();

private:
    int n;
    double tol;
    std::tr1::function<double(double)> f;
    static double defaultFunction(double x);
};

#endif // _ROOTFINDER_H_
