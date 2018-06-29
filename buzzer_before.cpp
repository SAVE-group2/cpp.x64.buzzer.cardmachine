/*******************************************************************************
* Function              : ApiBuzzer
* Argument              : None
* Return                : None
* Description           : 
* Example               : 
*******************************************************************************/
void ApiBuzzer(unsigned int type, unsigned int cnt, unsigned int on, unsigned int off)
{
    struct buzzer_param buzzer;

    buzzer.type = type;
    buzzer.count = cnt;
    buzzer.mson = on;
    buzzer.msoff = off;

    if (ioctl(fd_buzzer, BUZZER_TONE, &buzzer) < 0)
    {
        return;
    }
    usleep((on+10)*1000);
}


void dev_BEEP_play_sound (BYTE nBeeptype)
{
    unsigned int type=0;
    
    if ( use_beep == FALSE )
        return ;    
        
    switch( nBeeptype)
    {
    case BEEP_NO:
        return ;
    case BEEP_OK:
        ApiBuzzer( 1, 2, 80, 5);
        break;
    case BEEP_ERROR:
        ApiBuzzer( 7, 2, 100, 10);
        break;
    case BEEP_KEY:
        ApiBuzzer( 4, 1, 80, 0);
        break;
    case BEEP_START:
        ApiBuzzer(1, 1, 100, 0);
        ApiBuzzer(4, 1, 100, 0);
        ApiBuzzer(7, 1, 100, 0);
        break;
    }
}