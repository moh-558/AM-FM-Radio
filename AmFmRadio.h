#ifndef _CARRADIO_H
#define _CARRADIO_H
#define ARR_SIZE 5		//size
#define FRE_ARR 4		//size
#pragma warning (disable:4996)

/* -- this is a FILEHEADER COMMENT --
	NAME	:	AmFmRadio.h
	PURPOSE :	This header filae contains the class definition,
				and methods prototypes.
				
*/



// struct hold Am frequency and Fm frequency 
struct Freqs
{
	int AMFreq;
	double FMFreq;
	
};


/* -------------------------------------------------------------
	NAME	:	AmFmRadio
	PURPOSE :	The porpuse of this class is to repereset radio
				information in Am and Fm frequencies

   ------------------------------------------------------------- */
class AmFmRadio
{
private:
	/* ====================================== */
	/*              PRIVATE                   */
	/* ====================================== */
	/* -------------- ATTRIBUTES ------------ */
	Freqs	button[ARR_SIZE];		// number of buttons
	Freqs	prevStation;			// track previous frequency
	int		endVolume;				// track previous volume
	double	current_station;		// track the current station
	char	frequency[3];			// number of frequencies (Am,Fm)
	int		volume;					// radio volume
	bool	on;						
	bool	displayOutput;
	bool	check;

public:
	//sets the each button to the lowest frequency, sets the current station, sets the
	//frequency to AM, sets the volume to 0 and sets on to false, sets previous station
	// Am to 530, sets previous station to Fm to 87.9, sets displayoutput to false, sets
	// last volume entered to 0
	AmFmRadio(bool valueOn);
	AmFmRadio(bool valueOn, Freqs intialValues[]);

	// destructor to print out message
	~AmFmRadio();

	//sets on to true
	void PowerToggle(void);

	//returns a true if the radio is currently powered on, and false if the radio is in
	//the off position
	bool IsRadioOn();

	//toggles frequency between AM and FM and sets current station
	void ToggleFrequency(void);

	//sets button with current station by being passed a button number
	int SetButton(int button_num);

	//sets current station by being passed a button number
	int SelectCurrentStation(int button_num);

	//sets volume
	int SetVolume();
	int SetVolume(int RadioVolume);

	//validate to display any output from methods
	bool SetDisplayOutput(void);

	//shows volume, button settings, current station, AM or FM
	void ShowCurrentSettings(void);

	// validate the station
	bool SetCurrent_statuion();

	//changes frequency up in increments of .2 for FM, 10 for AM
	void ScanUp(void);
	//changes frequency down in decrements of .2 for FM, 10 for AM
	void ScanDown(void);
	

	//Accessors
	double GetCurrentStation(void); 
	Freqs GetRadioPreset(void);
	char* GetCurrentBand(void);
	int	GetVolume(void);
	bool GetDisplayOutput(void);
	Freqs	GetPrevStation(void);
	
	

};
#endif