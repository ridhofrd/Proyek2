#include <stdio.h>
#include <stdlib.h>
#include "RSA.h"
#include "vigenere_dekrip.h"
#include "vigenere_enkrip.h"
#include "hilldekrip.h"
#include "hillenkrip.h"
#include "opsi2.h"
#include "auth.h"
#include "commons.h"
#include "deskripsi_vernam.h"
#include "enkripsi_vernam.h"
#include "mhsDashboard.h"
#include "modul.h"
#include "welcome.h"
#include "Logout.h"
#include "datamenfess.h"
#include <conio.h>



int main()
{
    int firstState, secondState, thirdState;
    loading();
    system("cls");
    firstState = pilihanLoginWelcome();

    if(firstState == 1){

    }
    else if(firstState == 2){

    }
    else if(firstState == 3){

    }
    else
        return 0;
}
