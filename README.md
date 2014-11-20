Hjemmeeksamen2
==============

Koden for oppsett av klient og server, altså første del i client.c og server.c er hentet fra kursets sider. Har forhørt meg med gruppelærer om at dette er ok. 

hjemmeeksamen2.c
----------------
starter programmet med ./client maskinnavn portnummer
Har en kommandoløkke som løper evig helt til bruker taster 'q'.
Oppretter en ny klient for hvert gyldige brukeren taster inn. 

client.c
--------
Klienten opprettes og kobler seg til serveren med den gitte ip-adressen og port-nummeret.

Oppretter så en struct av typen packet som representerer headerinformasjonen som skal sendes til serveren. Headerinformasjonen består av lengden til meldingen som skal sendes til severen. Jeg har valgt kun dette fordi det er den eneste informasjonen jeg trenger for å vite
hvor lang meldingen jeg skal motta er. På denne måten vet jeg da om jeg har mottatt hele meldingen eller ikke. Grunnen til at jeg
har valgt en struct som headerinformasjon, er fordi den har en fast størrelse, slik at når  klient og server mottar headerinformasjon vet de på forhånd hvor stor den skal være.

For å sende headerinformasjonen oppretter jeg en char* til å peke på structen. Dette gjør jeg fordi jeg ikke vet om klienten klarer å sende hele structen i en pakke, og man kan derfor på denne måten sende de resterende bytes'ene om jeg sender structen som en vanlig char*. Headerinformasjonen sendes med funksjonen sendmessage() fra filen messages.c

Nyttelasten sendes så som en melding ved hjelp av funksjonen sendmessage(). 

Når klienten skal motta fra serveren, fungerer dette på akkurat samme måte som ved sending til server, men motsatt. Oppretter altså en struct med headerinformasjon fra server, leser så inn nyttelas med lengde lik den som er oppgitt i nyttelasten ved hjelp av funksjonen readmessage().

Skriver så resultatet fra server til skjerm. 

servermain.c
------------
starter programmet med ./server portnummer
Hovedprogrammet på serversiden. Kaller på funksjonen createserver() i server.c

server.c
--------
Kobler seg opp mot klient med gitt portnummer. Løper så i evig løkke frem til den mottar 'q' fra klient. 

På samme måte som i klienten opprettes det en struct for headerinformasjon fra klient, og bruker dette til å lese inn riktig lengde på nyttelasten. 

Dersom nyttelasten er 'q' avsluttes serveren.
Dersom nyttelasten er 'ls', 'pwd' eller 'cat' opprettes det en char* som skal holde på resultatet fra systemkallene. Kjører så popen med det ønskede kallet, leser dette inn i resultat-pekeren, oppretter headerinformasjon med lengden på resultatet fra popen, sender headerinformasjon og deretter nyttelast til klient. 

messages.c
----------
readmessage()
får inn socket, lengden på det som skal sendes og det som skal sendes. Løper i løkke frem tom. det som skal leses er lest. Dersom read() returnerer en verdi mindre enn 0, har det skjedd noe feil og det skrives ut en feilmelding. 
Dersom det fortsatt er mer igjen å lese etter at løkka er ferdig, har ikke alle dataene blitt lest. 

sendmessage()
fungerer på akkurat samme måte som readmessage.
