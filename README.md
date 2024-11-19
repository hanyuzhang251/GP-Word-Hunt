# GP Word Hunt
 
## How do I run this
1. download the entire project
2. edit main.cpp and set the dir variable to the directory the project is in (path to the project folder). To get the path of the project on mac, locate the downloaded folder in binder, select the folder, and press option + command + C to copy the path. Then, in main.cpp locate the dir variable on line 11. The line should look like `const std::string dir = "/Users/hanyuzhang/Documents/GitHub/GP-Word-Hunt";`. Delete the text inside the double quotes and paste in the path you collected. Save the file and close it.
3. To run the project, first make sure that you have a working version of a c++ compiler. Once that is done, in your terminal run `g++ -std=c++17 [path to main.cpp] -o [name of program]`. This will compile the program. When you're ready to run it, in the same terminal window run `./[name of program]`

## What does it do
After like everything loads, put in the word hunt chart left to right for each row and top to bottom. After a few seconds it should start outputting the answers in the order longest to shortest. After you put the word in on the wordhunt, type anything then press enter.
