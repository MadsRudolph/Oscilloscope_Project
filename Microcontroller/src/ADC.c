#include <avr/interrupt.h> // inkludere interrupt funktioner

void init_ADC_kanal0() // ADC0 er på Analog 0 pin på arduino board
{
    ADMUX = (1 << REFS0); // dette vælger refference spæningen på 5V for ADC, kan ses i oplæget for lektion 12: S.289
                          // Alle MUXn bits er sat lav dette vælger kanal 0 som indput og en gain på N/A : S.290 Table 26-4

    ADCSRA |= (1 << ADEN); // dette enabler adc se på datablad side: S.292
    ADCSRA |= (1 << ADSC); // ADSC starter sample på ADC'en den første sample tager længere,
                           // så derfor at det godt at køre den en gang i initialisering: s.293

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // indstiller prescaler værdi til ADC tælleren.
                                                          // Denne kombination giver en prescale på 128, hvilket bliver til 125kHz med F_CPU = 16MHz: S.293
                                                          // tællerfrekvensen har indflydelse på hvor hurtigt adc'en kan oversætte en analog indput spæning
                                                          // til en digital output værdi. Det tager 13 clock cykler(S.289) at konvatere indgangs spæningen
                                                          // så med 125KHz ser regnestykker således ud: 125KHz/13 = 9.6KHz, dette er den maksimale sample rate

    ADCSRA |= (1 << ADIE); // ADIE aktivere ADC interrupt, sådan at når et sample er færdig aktivere et interrupt: S.293

    ADCSRA |= (1 << ADATE);                // ADATE lukker op for auto trigger af ADC'en, hvad trigerren er vælges i ADCSRB: S.293
    ADCSRB |= (1 << ADTS2) | (1 << ADTS0); // Disse to bits vælger ADC auto trigger til at være TIMER1 compare match B: S.295
}

void init_timer1(int top_value)
{
    TCCR1A = 0; // slukker timer 1 a register så det ikke overskriver b register
    TCNT1 = 0;

    TCCR1B |= (1 << WGM12) | (1 << CS11); // sætter timer tildstanden til CTC på grund af WGM11 og indstiller en prescale værdi på 8: S.148 & S.161
    OCR1A = 40000; // denne linje gør at TCNT1 registret tæller op til 104 før det genstarter fra nul og aktivere interrupt i proccesen
                   // en prescaler på 8 og OCR1A værdi på 104 og F_CPU på 16MHz giver en output frekvens på cirka 9.524KHz meget tæt på de ønskede 9.5KHZ **40000 = 50Hz 
                   // selvom vi bruger TIMER1B registrende for det meste, er det stadig OCR1A som sætter topværdi i mode 4 som vi er i.

    TIMSK1 |= (1 << OCIE1B); // dette bit initialisere timer interrupt: S.166
}

// ISR(TIMER1_COMPB_vect){} **Husk at tilføje denne service rutine i dit program, ellers ville det crasher når timer1 compare match interrupt opfyldes