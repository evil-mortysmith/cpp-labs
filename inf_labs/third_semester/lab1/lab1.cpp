#include <iostream>
#include <random>
#include <fstream>

class ADice {
public:
    virtual unsigned roll() = 0;
};

class Dice : public ADice{
public:
    Dice(unsigned max, unsigned seed) : 
        max(max), dstr(1, max), reng(seed) {}
    
    unsigned roll() override {
        return dstr(reng);
    }

private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class ThreeDicePool : public ADice{
public:
    ThreeDicePool(unsigned max, unsigned seed_1, unsigned seed_2, unsigned seed_3) : max(max), 
        d1(max, seed_1), d2(max, seed_2), d3(max, seed_3){}

    
    
    unsigned roll() override {
        return d1.roll() + d2.roll() + d3.roll();
    }

private:
    unsigned max;
    Dice d1, d2, d3;
};

class PenaltyDice : virtual public ADice {
    public:
        PenaltyDice(ADice& d) : d(d) {}

        unsigned roll() override {
            unsigned roll_1 = d.roll(), roll_2 = d.roll();
            if (roll_1 <= roll_2) {
                return roll_1;
            }
            else {
                return roll_2;
            }

        }

    private:
        ADice& d;

};

class BonusDice : virtual public ADice {
    public:
        BonusDice(ADice& d) : d(d) {}

        unsigned roll() override {
            unsigned roll_1 = d.roll(), roll_2 = d.roll();
            if (roll_1 >= roll_2) {
                return roll_1;
            }
            else {
                return roll_2;
            }

        }

    private:
        ADice& d;

};

class DoubleDice : public PenaltyDice, public BonusDice {
    DoubleDice(ADice& d) : PenaltyDice(d), BonusDice(d) {}

    unsigned roll() override {
        return PenaltyDice::roll() + BonusDice::roll();
    }

};



class DoubleDice2 : public ADice{
    public:
    DoubleDice2(ADice& d) : d1(d), d2(d){}

    
    
    unsigned roll() override {
        return d1.roll() + d2.roll();
    }

private:
    PenaltyDice d1;
    BonusDice d2;
};



double expected_value(ADice &d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

double value_probability(unsigned value, ADice &d, unsigned number_of_rolls = 1) {
    unsigned count = 0;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt){
        unsigned cur_value = d.roll();
        if (cur_value == value) {
            count += 1;
        }
    }
    return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}

void writeFile(ADice &d, unsigned max, std::string name){
    std::string filename = name + ".txt";
    std::ofstream outFile(filename);

    for (int i = 0; i < max; ++i) {
        outFile << value_probability(i, d, 1000000) << "\n";
    }

    outFile.close();
    std::cout << "Массив успешно записан в файл!" << std::endl;


}




int main() {
    ThreeDicePool d(6, 45, 34, 12);
    std::cout << expected_value(d, 500) << '\n';

    Dice d0(100, 23);
    std::cout << value_probability(1, d0, 100000) << '\n';

    Dice d1(100, 42);
    //writeFile(d1, 100, "dice");


    PenaltyDice d2(d);
    //writeFile(d2, 100, "penalty_dice");
  

    BonusDice d3(d);
    //writeFile(d3, 100, "bonus_dice");

    ThreeDicePool d4(6, 1, 2, 3);
    //writeFile(d4, 18, "three_dice_pool");

    DoubleDice2 d5(d);
    //writeFile(d5, 200, "double_dice");
    std::cout << expected_value(d5, 100000) << '\n';


}