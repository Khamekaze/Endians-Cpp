# Endians Cpp
 
Listan med tal som ska hanteras görs genom att generera slumptal mellan 1 och 65535 som skrivs till en outputfil genom en ofstream.
När genereringen är klar så stängs filen.

Därefter skapar jag en inputström för att läsa in talen från filen jag skapade och två outputströmmar, en för att skriva till en fil för tal som är
konverterade till little endians och en för att skriva till en fil för chars skapade av dom mittersta bitarna av little endians.

Jag valde att läsa in talen som ska hanteras från den genererade filen som en ström där jag manipulerar värdena och skriver resultaten rad för rad efterhand istället
för att läsa in hela filen i exempelvis en array och sedan läser och manipulerar värden i en senare for-loop då syntaxen och även läsligheten u slutändan är bättre.
Att hantera hela processen genom strömmar gör också att jag slipper skapa onödigt många variabler och arrayer då variabler kan återanvändas och skrivas över efter att
outputströmmen har tagit emot dom.
Denna metod tar dock inte i beaktning väldigt stora filer då programmet själv genererar urspungsfilen vilket ger oss
full kontroll över storleken på filen, men en lösning hade kunnat vara att stänga strömmen vid ett visst maxindex, skriva datan till disk, och sedan öppna strömmen igen och fortsätta vid det sparade indexet tills filen är komplett.

För varje tal i strömmen utförs en konvertering till little endian format, detta görs med följande kod:
unsigned short toLittleEndian(unsigned short input) {
    return (input >> 8) | (input << 8);
}

Då jag genererar talen själv så vet jag att jag bara behöver hantera 16 bitars unsigned shorts i denna funktionen
och kan därför använda mig av en enkel OR bitmaskning och bitskiftning.


Nästa steg är en manipulering av den nya little endian shorten där jag skapar en char av dom 8 mellersta bitarna med följande kod:
unsigned char middleByte(unsigned short input) {
    unsigned char c = (input >> 4);
    return c;
}

Eftersom jag konverterar en 16 bitars unsigned short till en 8 bitars unsigned char så är processen väldigt simpel då jag endast behöver bitskifta
shorten 4 steg åt höger för att få ut rätt värde då konverteringen till char automatiskt kapar dom vänsterliggande 8 bitarna.

Det sista steget är att skicka dom nya manipulerade talen till respektive ström. Detta görs med två funktioner som båda tar emot en referens till en ström
samt ett värde att skriva. Funktionerna formatterar datan som ska skrivas och skriver in det i strömmarna.
Jag valde att inte skriva ut själva charen i outputfilen för dom mittersta bitarna då olika teckenkodningar gav väldigt olika tecken vid skrivning till fil och jag hittade inget bra sätt att lösa det på efter att ha läst om att locales och BOM-filer skulle kunna vara lösningen.
Jag valde att skriva ut charen i decimalt och binärt format istället.

När hela inputfilen har gåtts igenom stängs samtliga strömmar och filerna och dess data sparas på disk.
