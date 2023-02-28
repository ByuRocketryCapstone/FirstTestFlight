#include "Controller.h" 

Controller::Controller(double kp, double ki, double kd, double h0, double V0)
{
    // Set values of the PID constants
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

    mecoHeight = h0;
    mecoVelocity = V0;

    // Initialize paddle deployment angle values
    ref_alpha = 0;
    cmd_alpha = 0;

    loadData();  
    selectedTrajectoryNum = 1;  //FIXME: add functionality to choose between trajectories 
}


// Loads data for the reference trajectory from the file specified by dataFile. 
void Controller::loadData()
{
    string dataFile = selectFile();
    
    // Open input file stream
    ifstream reader(dataFile);
    if(!reader.is_open())
    {
        cout << "Data file failed to open in Controller::loadData()." << endl;
    }

    string line;
    for(int i = 0; i < REF_HEADER_SIZE; i++) getline(reader, line);  //skip header

    // read each line of the data file
    while(getline(reader, line))
    {
        vector<string> dataVals = split(line, ',');     //split line into individual values
        refTimes.push_back(stod(dataVals.at(0)));
        refHeights.push_back(stod(dataVals.at(1)));
        refVelocities.push_back(stod(dataVals.at(2)));
        refAccels.push_back(stod(dataVals.at(3)));
    }

    // cout << refTimes.size() << endl;
    // cout << refHeights.size() << endl;
    // cout << refVelocities.size() << endl;
    // cout << refAccels.size() << endl;
}


string Controller::selectFile()
{
    char selectedFileName[64];

    indexFile.open("index.txt", FILE_READ);
    if(!indexFile)
    {
        Serial1.println("Index file failed to open in Controller::loadData().");
        return;
    }

    double selectedHeight = 0, selectedVelocity = 0;
    double HEIGHT_THRESHOLD = 40;   //m
    double currHeight, currVelocity;
    char filename[64];

    char line[256] = indexFile.read();
    currHeight = sscanf(strtok(line, ' '), "%lf", &currHeight);
    selectedHeight = currHeight;
    selectedVelocity = currVelocity;
    selectedFileName = filename;

    while(reader >> currHeight)
    {
        reader >> currVelocity >> filename;
        if (abs(mecoVelocity-currVelocity) < abs(mecoVelocity-selectedVelocity) 
            && abs(mecoHeight-currHeight) < HEIGHT_THRESHOLD)
            {
                selectedHeight = currHeight;
                selectedVelocity = currVelocity;
                selectedFileName = filename;
            }
    }

    return REF_DIRECTORY + selectedFileName;
}


// Runs the PID algorithm to calculate a new paddle deployment angle. Input values are the 
// current values of the rocket in real time, not the optimal reference values
double Controller::calcAngle(double currTime, double currHeight, double currVelocity, double currAccel)
{ 
    ref_alpha = getCurrentAngle();

    double error_h = currHeight - getRefHeight(currTime);
    //cout <<"t: " << currTime << ", h: " << error_h << endl;
    double error_v = currVelocity - getRefVelocity(currTime);
    double error_a = currAccel - getRefAccel(currTime);

    //Actual PID Magic

    //cmd_alpha = ref_alpha + (error_v * kp) + (error_h * ki) - (error_a * kd);
    //cout << cmd_alpha << endl;

    //Trigger band antiwindup scheme (trying to improve robustnesss)
    if (abs(error_v) > getRefVelocity(currTime) * .15) cmd_alpha = ref_alpha + (error_v * kp) - (error_a * kd);
    else if (abs(error_v) <= getRefVelocity(currTime) * .15) cmd_alpha = ref_alpha + (error_v * kp) + (error_h * ki) - (error_a * kd); 


    //This is our saturation limits so we dont break things cause that would cause mucho problems
    if (cmd_alpha >= 70 * (M_PI/180)) cmd_alpha = 70 * (M_PI/180);
    else if (cmd_alpha <= 0) cmd_alpha = 0;
    else cmd_alpha = cmd_alpha;

    return cmd_alpha;
}


// Helper function that splits a line into individual strings according to the specified 
// delimiter character
std::vector<std::string> Controller::split(const std::string& text, char delimiter)
{                                                                                                                                                                                             
   std::vector<std::string> splits;                                                                                                                                                           
   std::string split;                                                                                                                                                                         
   std::istringstream parser(text);                                                                                                                                                                  
   while (std::getline(parser, split, delimiter))
   {
      splits.push_back(split);
   }
   return splits;
}


// Ping the hardware to determine the actual angle that the paddles are currently deployed to
double Controller::getCurrentAngle()
{
    return 0.0; //FIXME: Implement this
}


// Find the closest reference time index to the specified time
int Controller::findTimeIndex(double t)
{
    for (int i = 0; i < refTimes.size(); i++)
    {
        if(refTimes.at(i) > t) return i;  //return time index above the specified time value  
    }
    //cout << "Didn't find index" << endl;
    return refTimes.size()-1;  //index was not found
}


// Calculate reference height at specified time using linear interpolation
double Controller::getRefHeight(double t)
{
    unsigned int upperBound = findTimeIndex(t);
    unsigned int lowerBound = upperBound - 1;
    double refHeight = refHeights.at(lowerBound) + 
        (t-refTimes.at(lowerBound)) * (refHeights.at(upperBound)-refHeights.at(lowerBound)) /
        (refTimes.at(upperBound)-refTimes.at(lowerBound));
    
    return refHeight;
}


// Calculate reference velocity at specified time using linear interpolation
double Controller::getRefVelocity(double t)
{
    unsigned int upperBound = findTimeIndex(t);
    unsigned int lowerBound = upperBound - 1;
    double refVelocity = refVelocities.at(lowerBound) + 
        (t-refTimes.at(lowerBound)) * (refVelocities.at(upperBound)-refVelocities.at(lowerBound)) /
        (refTimes.at(upperBound)-refTimes.at(lowerBound));
    
    return refVelocity;
}


// Calculate reference accleration at specified time using linear interpolation
double Controller::getRefAccel(double t)
{
    unsigned int upperBound = findTimeIndex(t);
    unsigned int lowerBound = upperBound - 1;
    double refAccel = refAccels.at(lowerBound) + 
        (t-refTimes.at(lowerBound)) * (refAccels.at(upperBound)-refAccels.at(lowerBound)) /
        (refTimes.at(upperBound)-refTimes.at(lowerBound));
    
    return refAccel;
}


int Controller::getTrajectoryNum()
{
    return selectedTrajectoryNum;
}