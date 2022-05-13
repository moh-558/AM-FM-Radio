/* -- this is a FILEHEADER COMMENT --
	NAME	:	driver.ccp
	PURPOSE :	This program shows how is the radio work by displaying 
				menu to the user asking him to make a selection, first 
				the user should turn the radio on in order to be able 
				to play with the radio options, the user can select 
				station and vloume and can set buttons too.
*/
#include <stdio.h>
#include <stdlib.h>
#include "AmFmRadio.h"

#include <iostream>
using namespace std;

/* ---------------------------------------------------------------------
 * In case you haven't seen an "enum" declaration before, here are a 
 * couple of links to you to check out and read up about them ...
 * the concept of an "enum" is simple and is truly meant to clean up your
 * code and make it more readable ...
 *   1. https://www.codesdope.com/c-enum/
 *   2. https://en.cppreference.com/w/c/language/enum
 *   3. https://www.programiz.com/c-programming/c-enumeration
 * --------------------------------------------------------------------- */
enum menuItems
{
	kMenuNothing = 0,	// special constant for initialization only
	kMenuTogglePower = 1, kMenuSetVolume, kMenuToggleAMFM, kMenuSetButton, kMenuSelectButton,
	kMenuShowCurrentSettings, kMenuScanUp,KMenuScanDown, kMenuQuit
};


int main()
{
	
	int			volume_OK = 0;
	int			button_OK = 0;
	int			button_num = 0;
	menuItems	choice = kMenuNothing;
	char		buf[20] = {0};
	AmFmRadio	jazzy(false);
	bool		on = false;
	
	cout << "a";
	do
	{
		printf("\n\nMAIN MENU\n");
		printf("=========\n\n");
		printf("1.  Toggle Power\n");
		printf("2.  Set Volume\n");
		printf("3.  Toggle AM / FM\n");
		printf("4.  Set a Button \n"); 
		printf("5.  Select a Button \n"); 
		printf("6.  Show Current Settings\n"); 
		printf("7.  Scan Up \n"); 
		printf("8.  Scan Down \n");
		printf("9.  Quit the Program\n");
		printf("\nMake a selection from the menu\n");
		fgets(buf, sizeof buf, stdin);
		choice = (menuItems) atoi(buf );
		
		switch( choice )
		{
		case kMenuTogglePower:
			jazzy.PowerToggle();
			break;
		case kMenuSetVolume: 
			volume_OK = jazzy.SetVolume();
			if( volume_OK == 0 )
			{
				printf("\nVolume was set to 0.");
			}
			else if( volume_OK == 2 )
			{
				printf("\nVolume was set to 100.");
			}
			break;
			
		case kMenuToggleAMFM:
			on = jazzy.IsRadioOn();
			if( on )
			{
				jazzy.ToggleFrequency();
			    
			}
			else
			{
				printf("\nThe radio must be turned on before the "
					"band can be toggled!");
			}
			break;
		case kMenuSetButton:
			on = jazzy.IsRadioOn();
			if( on )
			{
				printf("\nWhich button do you want to set?");
			    fgets(buf, sizeof buf, stdin);
			    button_num = atoi(buf) - 1;
			    button_OK = jazzy.SetButton(button_num);
			    if( button_OK == 0 )
				{
					printf("\nYou entered an invalid button number!");
				}
			}
			else
			{
				printf("\nYou must turn the radio on before you set the buttons!\n");
			}
			break;
		case kMenuSelectButton:
			on = jazzy.IsRadioOn();
			if( on )
			{
				printf("\nEnter the number of the button: ");
			    fgets(buf, 20, stdin);
			    button_num = atoi(buf) - 1;
			    button_OK = jazzy.SelectCurrentStation(button_num);
				if( button_OK == 0 )
				{
					printf("\nYou entered an invalid button number!");
				}
			}
			else
			{
				printf("\nYou must turn the radio on before you set the buttons!\n");
			}
			break;
		case kMenuShowCurrentSettings:
			jazzy.ShowCurrentSettings();
			break;
		case kMenuScanUp:
			on = jazzy.IsRadioOn();
			if( on )
			{
				jazzy.ScanUp();
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan button!\n");
			
			}
			break;
		case KMenuScanDown:
			on = jazzy.IsRadioOn();
			if (on)
			{
				jazzy.ScanDown();
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan button!\n");

			}
			break;
		case kMenuQuit:
		    break;
		default:
			printf("You have entered an invalid selection. Please make \n"
				   "another selection.\n");
			break;

		}

		if( (choice != kMenuShowCurrentSettings) && (choice != kMenuQuit) )
			jazzy.ShowCurrentSettings();

	}while( choice != kMenuQuit ); // loop until the user choses 9 in menu

	printf("\nGoodbye!\n");
	return 0;


}