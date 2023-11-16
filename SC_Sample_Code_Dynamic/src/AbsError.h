#pragma once
#include <string>

// holds the error
class AbsError
{
private:
    // Sum of Absolute Error
    double _sum_err;

    // Sum of Absolute Percentage Error
    double _per_err;

    // Miximum value of Absolute Error
    double _max_abs;

    // Miximum value of Absolute Percentage Error
    double _max_per;

    // Minimum value of Absolute Error
    double _min_abs;

    // Minimum value of Absolute Percentage Error
    double _min_per;

protected:
    // Trials
    unsigned int _time;

public:
    /// @brief Constructor
    AbsError();
    virtual ~AbsError() = default;

    /// @brief Update the value
    /// @param ans Correct value
    /// @param val The value of output SN
    virtual void Update(const double& ans, const double& val);

    /// @brief Reset the parameters
    void reset();
     
    /// @brief Return Mean Absolute Error (MAE)
    /// @return MAE
    double get_MAE() {return _sum_err/double(_time); };

    /// @brief Return Mean Absolute Percentage Error (MAPE)
    /// @return MAPE
    double get_MAPE() { return _per_err/double(_time); };

    /// @brief Return Maximum Absolute Error
    /// @return Max AE
    double get_MAX_AE() {return _max_abs; };

    /// @brief Return Maximum Absolute Percentage Error
    /// @return Max APE
    double get_MAX_APE() {return _max_per; };

    /// @brief Return Minimum Absolute Error
    /// @return Min AE
    double get_MIN_AE() {return _min_abs; };

    /// @brief Return Minimum Absolute Percentage Error
    /// @return Min APE
    double get_MIN_APE() {return _min_per; };

    /// @brief Print All Parameters
    virtual void  print_Summary() const;

    /// @brief Retrun All Parameters
    /// @return string
    virtual std::string get_Summary() const;
};