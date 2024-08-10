#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Define constants
#define MR_DESIRED 2.2
#define DESIRED_PRESSURE 100.0   // Example constant chamber pressure
#define SAMPLING_INTERVAL 100000 // Sampling interval in microseconds

// Define variables
float oxidizer_flow_rate = 0.0;
float fuel_flow_rate = 0.0;
float chamber_pressure = 0.0;
float fuel_valve_signal = 0.0;
float oxidizer_valve_signal = 0.0;

// Function Declaration
void read_sensors();
void calculate_errors(float mr_error, float pressure_error);
void update_control_signals(float mr_error, float pressure_error);
void send_control_signals(float fuel_signal, float oxidizer_signal);

float get_oxidizer_flow_rate();
float get_fuel_flow_rate();
float get_chamber_pressure();

void set_fuel_valve_signal(float signal);
void set_oxidizer_valve_signal(float signal);

int main()
{
    // Main control loop
    while (1)
    {
        float mr_error, pressure_error;

        // Read sensor values
        read_sensors();

        // Calculate errors
        calculate_errors(mr_error, pressure_error);

        // Update control signals
        update_control_signals(mr_error, pressure_error);

        // Send control signals to valves
        send_control_signals(fuel_valve_signal, oxidizer_valve_signal);

        // Sleep or delay if necessary
        usleep(SAMPLING_INTERVAL); 
    }

    return 0;
}

void read_sensors()
{
    // for actual sensor reading code
    oxidizer_flow_rate = get_oxidizer_flow_rate(); // The return value of the function will Assign to global variables  
    fuel_flow_rate = get_fuel_flow_rate();         
    chamber_pressure = get_chamber_pressure();     
}

void calculate_errors(float mr_error, float pressure_error)
{
    // Calculate mixture ratio error
    float current_mixture_ratio = fuel_flow_rate / oxidizer_flow_rate;
    mr_error = current_mixture_ratio - MR_DESIRED;

    // Calculate chamber pressure error
    pressure_error = chamber_pressure - DESIRED_PRESSURE;
}

void update_control_signals(float mr_error, float pressure_error)
{
    // Assemption (Simple proportional control) 
    float c_mixture = 1.0;  //( proportional Gain  )
    float c_pressure = 1.0; 

    // Adjust fuel and oxidizer valve signals based on errors
    fuel_valve_signal -= c_mixture * mr_error;           
    oxidizer_valve_signal -= c_pressure * pressure_error; 

    // Ensure control signals are within valid range (0 to 1) to open or close the valve............
    if (fuel_valve_signal >= 1.0)
        fuel_valve_signal = 1.0;
    else if (fuel_valve_signal <= 0.0)
        fuel_valve_signal = 0.0;
    if (oxidizer_valve_signal >= 1.0)
        oxidizer_valve_signal = 1.0;
    else if (oxidizer_valve_signal <= 0.0)
        oxidizer_valve_signal = 0.0;
}

void send_control_signals(float fuel_signal, float oxidizer_signal)
{
    set_fuel_valve_signal(fuel_signal);         // It will just print the value that will actually go to some actuvators.
    set_oxidizer_valve_signal(oxidizer_signal);
}

// functions for sensor reading and control signal setting
float get_oxidizer_flow_rate()
{
    return 1.0;
} 

// Example values
float get_fuel_flow_rate()
{
    return 1.0;
}

float get_chamber_pressure()
{
    return 100.0;
}

void set_fuel_valve_signal(float signal)
{
    printf("Fuel valve signal: %.2f\n", signal);
}

void set_oxidizer_valve_signal(float signal)
{
    printf("Oxidizer valve signal: %.2f\n", signal);
}
