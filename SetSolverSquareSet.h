#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h
#include <vector>


class SetSolverSquareSet
{
public:
    std::vector<int>set;
    SetSolverSquareSet(){
        for(int i =1; i < 10; i++){
            set.push_back(i);
        }
    }

  

};

#endif /* SetSolverSquareSet_h */
