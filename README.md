# OpenGL-projekt [TNM061]

Detta är ett "endless runner" spel som gjordes som ett projektarbete i kursen TNM061 (3D-Datorgrafik), Linköpings Universitet.


## VIKTIGT!

**_Koden är på vissa ställen väldigt dåligt dokumenterat_.**

  1. Användningen av std::vector är en ett val som gjordes pågrund utav smidighetsskäl. Gruppen är medvetna om dess ineffiktivitet och ber därför om ursäkt...
  2. Klassen "obstacles" är felimplementerad. Detta innebär att den ej är en subklass till "Elements", något som den egentligen ska vara.
  3. En del av de klasserna vi har är dumt skrivna då flera av dem har hand om och loggar samma data som redan finns på andra ställen. Detta är en bieffekt utav halvdåligt planerande och tidsbrist. Det absolut tydligaste exemplet av detta är att behandligen av data och sortering av data från olika vektorer. 
  4. Det läcker! Vi har inte lagt så mycket tid på korrekt hantering utav pointers (dvs destructors samt användning av 'delete'). 
  5. Valet av kollisionshanteringsmetod är **ENDAST** vald på grund av tidsbristen för en mer vettig lösning.
