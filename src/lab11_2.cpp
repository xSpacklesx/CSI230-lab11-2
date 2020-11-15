#include <boost/program_options.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <iostream>
#include <ctime>

using namespace boost::program_options;

//boost::random::mt19937
boost::random::mt19937 gen;


//@credit I did look at https://www.boost.org/doc/libs/1_71_0/doc/html/boost_random/tutorial.html for info on how to use the function but I tried to make it my own
//roll die function sets the seed of the generator to time and then picks a random number between 1 and the entered die size
int rollDie(int dieSize)
{
  gen.seed(std::time(0));
  boost::random::uniform_int_distribution<> dist(1, dieSize);
  return dist(gen);
}

//@credit got from Devin's lecture in part
int main(int argc, const char *argv[])
{
  try
  {
    options_description desc{"Options"};
    desc.add_options()
      ("help,h", "Help screen")
      ("die", value<int>(), "Die:");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
      std::cout << desc << '\n';
      //gets the die option and tells you what num you input
    else if (vm.count("die"))
      std::cout << "Rolling: d" << vm["die"].as<int>() << '\n';
      //callls the roll die with the imput cast as an int
      std::cout << "Rolled: " << rollDie(vm["die"].as<int>()) << std::endl;
  }
  catch (const error &ex)
  {
    std::cerr << ex.what() << '\n';
  }
}