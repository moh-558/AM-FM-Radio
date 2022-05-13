
/* -- this is a FILEHEADER COMMENT --
	NAME	:	AmFmRadio.ccp
	PURPOSE :	This source filae contains methods and accessors
				for AmFmradio class.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"


/*
	Name	: AmFmRadio -- CONSTRUCTOR
	Purpose : to instantiate AmFmRadio object given a set of attribute values, and to set attribute values
	Inputs	: bool valeOn	
	Outputs	:	NONE
	Returns	:	Nothing
*/
AmFmRadio::AmFmRadio(bool valueOn = false)
{
	// loop to set intitla values of the radio to 530 for AM frequency
	for (int i = 0; i < 5; ++i)
	{
		button[i].AMFreq = 530;
	}
	// loop to set intitla values of the radio to 87.9 for FM frequency
	for (int j = 0; j < 5; ++j)
	{
		button[j].FMFreq = 87.9;
	}
	// set the current station value to 530
	current_station = 530;
	//set frequency to AM
	strcpy(frequency, "AM");
	// set volume to 0
	volume = 0;
	// set previous station for Am frequency to 530
	prevStation.AMFreq = 530;
	// set previous station for Am frequency to 530
	prevStation.FMFreq = 87.9;
	// set last entered volume to 0
	endVolume = 0;
	// set displayoutput to false
	displayOutput = false;
	// set On to false 
	on = valueOn;
	check = false;
}

/*
	Name	: AmFmRadio -- CONSTRUCTOR
	Purpose : to instantiate AmFmRadio object given a set of attribute values, and to set attribute values
	Inputs	: bool valeOn
			  Freqs intialValues		Array of structs holds frequencies value
	Outputs	:	NONE
	Returns	:	Nothing
*/
AmFmRadio::AmFmRadio(bool valueOn, Freqs intialValues[])
{
	// loop to set intitla values of the radio to 530 for AM frequency
	for (int i = 0; i < 5; ++i)
	{
		button[i].AMFreq = intialValues[i].AMFreq;
	}
	// loop to set intitla values of the radio to 87.9 for FM frequency
	for (int j = 0; j < 5; ++j)
	{
		button[j].FMFreq = intialValues[j].FMFreq;
	}
	// set the current station value to 530
	current_station = 530;
	//set frequency to AM
	strcpy(frequency, "AM");
	// set volume to 0
	volume = 0;
	// set previous station for Am frequency to 530
	prevStation.AMFreq = 530;
	// set previous station for Am frequency to 530
	prevStation.FMFreq = 87.9;
	// set last entered volume to 0
	endVolume = 0;
	// set displayoutput to false
	displayOutput = false;
	// set On to false 
	on = valueOn;
	check = false;
}


/*
	Name	: AmFmRadio -- DESTRUCTOR
	Purpose : to destroy AmFmRadio object
	Inputs	: NONE
	Outputs	:	NONE
	Returns	:	Nothing
*/
AmFmRadio::~AmFmRadio()
{
	printf("Destroying AmFmRadio");
}


/*	Name	: PowerToggle
	Purpose : this method is to put the radio On or Off
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	Nothing											*/
void AmFmRadio::PowerToggle(void)
{
	//check if value of ON is false
	if( on == false )
	{
		// when it is false set it to true
		on = true;
		// set the volume to the last entered volume
		volume = endVolume;
	}
	else
	{
		
		on = false;
		// set volume to 0
		volume = 0;
	}
}

/*	Name	: IsRadioOn
	Purpose : this method is to ckeck if radio is on
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	returnss true or false										*/
bool AmFmRadio::IsRadioOn() 
{
	return on;
}

/*	Name	: SetVolume
	Purpose : this method is to prompt user to input volume value
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	return volume (int)											*/
int AmFmRadio::SetVolume()
{
	char buf[20] = "";

	printf("\nEnter the volume level (0 - 100). ");
	// take user input 
	fgets(buf, sizeof buf, stdin);
	// convert the 
	volume = atoi(buf);
	// calling this method to validate the volume the return it
	return SetVolume(volume);

}

/*	Name	: SetVolume
	Purpose : this method is to validate the volume (worker bee)
	Inputs	:	radioVolume		int 
	Outputs	:	NONE
	Returns	:	int (volume), 0 (volume is 0), (2 vulume is 100)		*/
int AmFmRadio::SetVolume(int radioVolume)
{
	int tracker = 0;
	
	if (radioVolume < 0) //if user enters volume less than 0, volume = 0
	{
		// set volume to 0
		radioVolume = 0;
		// set tracker to 0 that's mean volume is less than 0
		tracker= 0;
	}

	if (radioVolume > 100) //if user enters volume greater than 100, volume = 100
	{
		// set volume to 100
		radioVolume = 100;
		// set tracker to 2 that's mean volume is greater than 100
		tracker= 2;
	}
	
	//set volume to the radio volume 
	volume = radioVolume;
	//set last volume entered to volume
	endVolume = volume;
	return tracker;

}

/*	Name	: ToggleFrequency
	Purpose : this method is to set the frequency to AM,FM
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	Nothing											*/
void AmFmRadio::ToggleFrequency()
{
	//check if frequency is AM
	if( strcmp(frequency, "AM") == 0 )
	{
		// set frequency to FM
		strcpy(frequency, "FM");
		// Assign current station to the previous Fm frequency
		current_station = prevStation.FMFreq;
		
	}
	else
	{
		// sst frequency to AM
		strcpy(frequency, "AM");
		// Assign current station to the previuos Am frequency
		current_station = prevStation.AMFreq;
		
	}
}

/*	Name	: SetButton
	Purpose : this method is to set the buttons 1-5
	Inputs	:	int button_num  number of buttons
	Outputs	:	NONE
	Returns	:	frequency number									*/
int AmFmRadio::SetButton(int button_num)
{
	// check if the entered number within the range (1-5)
	if( (button_num >= 0) && (button_num <= 4) )
	{
		// check if frequency = AM
		if( strcmp("AM", frequency) == 0 )
		{
			// set button to the chosen station
			button[button_num].AMFreq = current_station;
		}
		else
		{
			// if freuency = FM, set button to the chosen station
			button[button_num].FMFreq = current_station;
		}
		return 1;

	}
	return 0;

}

/*	Name	: SelectCurrentStation
	Purpose : this method takes station and put to thhe button the user chooses
	Inputs	:	int button_num  number of buttons
	Outputs	:	NONE
	Returns	: 	int 										*/
int AmFmRadio::SelectCurrentStation(int button_num)
{
	// check if the entered number within the range (1-5)
	if( (button_num >= 0) && (button_num <= 4) )
	{
		// check if frequency = AM
		if( strcmp("AM", frequency) == 0 )
		{
			// set current station to chosen button
			current_station = button[button_num].AMFreq;
		}
		else
		{
			// if freuency = FM, set current station to chosen button
			current_station = button[button_num].FMFreq;
		}

		return 1;
	}
	return 0;


}

/*	Name	: ShowCurrentSetting
	Purpose : this method is print out the current radio information
	Inputs	:	NONE
	Outputs	:	current radio information
	Returns	:	Nothing											*/
void AmFmRadio::ShowCurrentSettings(void)
{
	//ckeck if radio is On
	if( on == true )
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nFrequency: %s\n", frequency);
	printf("Volume: %d\n", volume);
	printf("Current Station: %.1f %s\n", current_station, frequency);
	printf("AM Button Settings: ");
	// loop tp printout the buttons for AM
	for( int i = 0; i < 5; ++i )
	{
		printf("%d) %6d ", i + 1, button[i].AMFreq);
	}

	printf("\nFM Button Settings: ");
	// loop tp printout the buttons for FM
	for( int j = 0; j < 5; ++j )
	{
		printf("%d) %6.1f ", j + 1, button[j].FMFreq);
	}
 }

/*	Name	: ScanUp
	Purpose : this method is to increment radio frequency
			  incremet by 10 for Am, incerement by .2 for 
			  FM
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	Nothing											*/
void AmFmRadio::ScanUp(void)
{
	// check if frequency is AM
	if( strcmp("AM", frequency) == 0 )
	{
		//if current_station is 1700, the current_station becomes 530
		if( current_station == 1700 )
		{
			current_station = 530;
			
			
		}
		else
		{
			// if current_station is not 1700 increment it by 10
			current_station = current_station + 10;
			
			
		}
		// assign previous station for AM to current_station (hold the value)
		prevStation.AMFreq = current_station;
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if( current_station >= 107.9 )
		{
			current_station = 87.9;
			
		}
		else
		{
			// if current_station is not 107.9 increment it by .2
			current_station = current_station + .2;
		
			
		}
		// assign previous station for FM to current_station (hold the value)
		prevStation.FMFreq = current_station;
		
		
	}
	//check if displayoutput is false pritntout the message
	if (displayOutput == false)
	{

		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}

/*	Name	: ScanDown
	Purpose : this method is to increment radio frequency
			  decremet by 10 for Am, decerement by .2 for 
			  FM
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	Nothing											*/
void AmFmRadio::ScanDown(void)
{
	// check if frequency is AM
	if (strcmp("AM", frequency) == 0)
	{
		//if current_station is 530, the current_station becomes 1700
		if (current_station == 530)
		{
			current_station = 1700;
		}
		else
		{
			// if current_station is not 530 decrement it by 10
			current_station = current_station - 10;
		}
		// assign previous station for AM to current_station (hold the value)
		prevStation.AMFreq = current_station;
	}
	else
	{
		//if the current_station is 87.9, the current_station becomes 107.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station <= 87.9)

		{
			current_station = 107.9;
		}
		else
		{
			// if current_station is not 87.9 decrement it by .2
			current_station = current_station - .2;
		}
		// assign previous station for FM to current_station (hold the value)
		prevStation.FMFreq = current_station;
	}
	//check if displayoutput is false pritntout the message
	if (displayOutput == false)
	{

		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
	

}

/*	Name	: Setcurrent_satation
	Purpose : this method is to validate the station and set it
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	bool true or false										*/
bool AmFmRadio::SetCurrent_statuion()
{

	// check if frequency is AM
	if (strcmp("AM", frequency) == 0)
	{
		// assign current station to previous the return true 
		current_station = prevStation.AMFreq;
		check = true;
		return check;
	}
	// check if frequency is FM
	else if(strcmp("FM", frequency) == 0)
	{
		// assign current station to previous the return true 
		current_station = prevStation.FMFreq;
		check = true;
		return check;
	}

}

/*	Name	: SetDisplayOutput
	Purpose : this method is set diplayoutput value
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	bool true or false											*/
bool AmFmRadio::SetDisplayOutput()
{
	
	if (displayOutput == true)// check if displayOutput is true return true, false otherwise
	{
		return true;
	}
	return false;
}

/* -------------- ACCESSORS ------------ */

/*
	Name	: GetPrevStation
	Purpose : what is the previous station ?
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	struct contains the stations
*/
Freqs AmFmRadio::GetPrevStation(void)
{
	return prevStation;
}

/*
	Name	: GetCurrentStation
	Purpose : what is current station?
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	double (radio frequency)
*/
double AmFmRadio::GetCurrentStation(void)
{
	return current_station;
}

/*
	Name	: GetCurrentBand
	Purpose : copy frequency to temporary variable
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	char* eith frequencies
*/
char* AmFmRadio::GetCurrentBand(void)
{
	char tmp[FRE_ARR] = "";  // array of characters
	// copy the values to tmp
	strcpy(tmp,frequency);
	return tmp;
}

/*
	Name	: GetCurrentBand
	Purpose : copy frequency to temporary variable
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	char* with frequencies
*/
int AmFmRadio::GetVolume(void)
{
	return volume;
}

/*
	Name	: GetCurrentBand
	Purpose : copy frequency to temporary variable
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	char* eith frequencies
*/
bool AmFmRadio::GetDisplayOutput(void)
{
	return displayOutput;
}

/*
	Name	: GetRadioPreset
	Purpose : copy button to temporary variable
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	array of structs
*/
Freqs AmFmRadio::GetRadioPreset(void)
{
	// array of structs
	Freqs  tmp[ARR_SIZE];
	// loop to copy the values of buttons to the new variable, then return it
	for (int i = 0; i < 5; i++)
	{
		tmp[i] = button[i];

		return tmp[i];
	}

}
 
//(^_^)//