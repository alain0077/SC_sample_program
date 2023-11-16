#include "AbsError.h"
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

/// @brief Constructor
AbsError::AbsError() : _time(0), _sum_err(0.0), _per_err(0.0),
_max_abs(0.0), _min_abs(DBL_MAX), _max_per(0.0), _min_per(DBL_MAX)
{
}

/// @brief Update the value
/// @param ans Correct value
/// @param val The value of output SN
void AbsError::Update(const double& ans, const double& val)
{
    // Count up
    _time++;

    // Absolute Error
    double err = std::abs(ans - val);

    // Absolute Percentage Error
    double per = err / ans;

    // Compair and Update
    _max_abs = _max_abs > err ? _max_abs : err;
    _min_abs = _min_abs < err ? _min_abs : err;
    _max_per = _max_per > per ? _max_per : per;
    _min_per = _min_per < per ? _min_per : per;

    // Sum of Absolute Error
    _sum_err += err;

    // Sum of Absolute Percentage Error
    _per_err += per;
}

/// @brief Reset the parameters
void AbsError::reset()
{
    _sum_err = 0.0;
    _per_err = 0.0;
    _time = 0;
    _max_abs = 0.0;
    _min_abs = DBL_MAX;
    _max_per = 0.0;
    _min_per = DBL_MAX;
}

/// @brief Print All Parameters
void AbsError::print_Summary() const
{
    cout << "-----------------------------------" << "\n";
    cout << "|            About ERR            |" << "\n";
    cout << "-----------------------------------" << "\n";
    cout << " Trials : " << _time << "\n";
    cout << "------- Absolute Error (AE) -------" << "\n";
    cout << "    MAE : " << _sum_err/double(_time) << "\n";
    cout << " MAX AE : " << ((_max_abs > DBL_EPSILON) ? _max_abs : 0.0) << "\n";
    cout << " MIN AE : " << ((_min_abs > DBL_EPSILON) ? _min_abs : 0.0) << "\n";
    cout << "- Absolute Percentage Error (APE) -" << "\n";
    cout << "   MAPE : " << _per_err/double(_time) << "\n";
    cout << "MAX APE : " << ((_max_per > DBL_EPSILON) ? _max_per : 0.0) << "\n";
    cout << "MIN APE : " << ((_min_per > DBL_EPSILON) ? _min_per : 0.0) << "\n";
}

/// @brief Retrun All Parameters
/// @return string
string AbsError::get_Summary() const
{
    string s;

    s = "-----------------------------------\n";
    s += "|            About ERR            |\n";
    s += "-----------------------------------\n";
    s += " Trials : " +  to_string(_time) + "\n";
    s += "------- Absolute Error (AE) -------\n";
    s += "    MAE : " + to_string(_sum_err/double(_time)) + "\n";
    s += " MAX AE : " + to_string((_max_abs > DBL_EPSILON) ? _max_abs : 0.0) + "\n";
    s += " MIN AE : " + to_string((_min_abs > DBL_EPSILON) ? _min_abs : 0.0) + "\n";
    s += "- Absolute Percentage Error (APE) -\n";
    s += "   MAPE : " + to_string(_per_err/double(_time)) + "\n";
    s += "MAX APE : " + to_string((_max_per > DBL_EPSILON) ? _max_per : 0.0) + "\n";
    s += "MIN APE : " + to_string((_min_per > DBL_EPSILON) ? _min_per : 0.0) + "\n";
    
    return s;
}