/// \file IOHprofiler_csv_logger.hpp
/// \brief Head file for class IOHprofiler_csv_logger.
///
/// A detailed file description.
///
/// \author Furong Ye
/// \date 2019-06-27
#ifndef _IOHPROFILER_CSV_LOGGER_H
#define _IOHPROFILER_CSV_LOGGER_H

#include "../IOHprofiler_observer.hpp"
#include "../IOHprofiler_common.h"

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS

namespace fs = boost::filesystem;

/// \brief A class of logging csv files.
///
/// To activate logger functions as evaluating problems,  a 'logger' must be added to
/// IOHprofiler_problem by the statement 'problem.add_logger(logger)'.
class IOHprofiler_csv_logger : public IOHprofiler_observer {
public:
  IOHprofiler_csv_logger() {
    this->output_directory = "./";
    this->folder_name = "IOHprofiler_test";
    this->algorithm_name =  "algorithm";
    this->algorithm_info = "algorithm_info";
  };

  IOHprofiler_csv_logger(std::string directory, std::string folder_name,
                         std::string alg_name, std::string alg_info) {
    this->output_directory = directory;
    this->folder_name = folder_name;
    this->algorithm_name =  alg_name;
    this->algorithm_info = alg_info;
  }

  IOHprofiler_csv_logger(const IOHprofiler_csv_logger& other) {
    if (other.cdat.is_open()     ||
        other.idat.is_open()     ||
        other.dat.is_open()      ||
        other.tdat.is_open()     ||
        other.infoFile.is_open()) {
        throw std::runtime_error("Attempted to copy logger that isn't clear.");
    }

    this->folder_name = other.folder_name;
    this->output_directory = other.output_directory;
    this->algorithm_name = other.algorithm_name;
    this->algorithm_info = other.algorithm_info;
    this->suite_name = other.suite_name;
    this->dimension = other.dimension;
    this->problem_id = other.problem_id;
    this->instance = other.instance;
    this->problem_name = other.problem_name;
    this->found_optimal = other.found_optimal;
    this->optimal_evaluations = other.optimal_evaluations;
    this->last_dimension = other.last_dimension;
    this->last_problem_id = other.last_problem_id;
    this->logging_parameters = other.logging_parameters;
    this->logging_parameters_name = other.logging_parameters_name;
  }

  ~IOHprofiler_csv_logger() {
    this->clear_logger();
  };

  void activate_logger();
  void clear_logger();

  void target_problem(int problem_id, int dimension, int instance, std::string problem_name);
  void target_suite(std::string suite_name);

  void openInfo(int problem_id, int dimension, std::string problem_name);
  void write_info(int instance, double optimal, int evaluations);

  void write_line(const size_t &evaluations, const double &y, const double &best_so_far_y,
                 const double &transformed_y, const double &best_so_far_transformed_y);
  void write_line(const std::vector<double> &logger_info);
  void update_logger_info(size_t optimal_evaluations, double found_optimal);

  void set_parameters(const std::vector<std::shared_ptr<double>> &parameters);
  void set_parameters(const std::vector<std::shared_ptr<double>> &parameters, const std::vector<std::string> &parameters_name);

private:
  std::string folder_name;
  std::string output_directory;
  std::string algorithm_name;
  std::string algorithm_info;

  std::string suite_name = "No suite";

  // The information of logged problems.
  int dimension;
  int problem_id;
  int instance;
  std::string problem_name;

  std::fstream cdat;
  std::fstream idat;
  std::fstream dat;
  std::fstream tdat;
  std::fstream infoFile;

  std::vector<double> found_optimal;
  size_t optimal_evaluations;

  int last_dimension = 0;
  int last_problem_id = -1;
  
  std::vector<std::shared_ptr<double>> logging_parameters; /// < parameters to be logged as logging evaluation information.
  std::vector<std::string> logging_parameters_name; /// < name of parameters to be logged as logging evaluation information.

  /// \fn std::string IOHprofiler_experiment_folder_name()
  /// \brief return an available name of folder to be created.
  std::string IOHprofiler_experiment_folder_name();
  int IOHprofiler_create_folder(const std::string path);

  void write_header();

  /// \fn openIndex()
  /// \brief to create the folder of logging files.
  int openIndex();
};

#endif //_IOHPROFILER_CSV_LOGGER_H
