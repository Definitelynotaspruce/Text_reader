# Text_reader
## Pasikartojančių žodžių paieška tekste, link'ų radimas

## Programos paskirtis
* Suskaičiuoti, kiek kartų pasikartoja vienodi žodžiai tekste
* Tekste surasti bei išspausdinti link'us

### Analizuojamas tekstas iš https://diktantas.lt/news/Nacionalinio-diktanto-tekstas

## Programos veikimas

### 1. *.txt* failo nuskaitymas

Duomenų saugojimui naudojamas asociatyvus **std::map** konteineris
``` shell
std::map<std::string, std::pair<int, std::vector<int>>>
```
* **Key** *std::string* tipo elementas saugantis pasikartojančius žodžius
* **Value** *std::pair*, kuris sudarytas iš dviejų (poros) elementų derinio: 
  * *int* - naudojamas pasikartojimų skaičiui saugoti
  * *std::vector<int>* -  skirtas saugoti eilučių, kuriose pasikartoja žodis, numerius.
 
### 2. Simbolių tikrinimas
``` shell
for (auto &w : word)
     if (ispunct(w) || isdigit(w)) 
        word.erase(std::remove(word.begin(), word.end(), w), word.end());
```
Patikrinimui naudojamos ispunct() bei isdigit() funkcijos.
Jeigu tikrinimo metu yra randamas netinkamas simbolis, jis yra ištrinamas.

### 3. URL tikrinimas
``` shell
std::vector<std::string> url = {"http", "www."};
    for (auto u : url)
        if (word.substr(0, 4) == u)
            return true;
```
Tikrinama, ar nuskaityto elemento pirmieji simboliai sutampa su URL.

### 4. Išvedimas

Rezultatai išvedami į *results.txt* failą.
Tiksliam lygiavimui naudojama funkcija
``` shell
str.length() - std::count_if(str.begin(), str.end(), [](char c) -> bool { return (c & 0xC0) == 0x80; })
``` 
Ji suskaičiuoja tikslų reikalingų padėti tarpelių skaičių (nes dėl lietuviškų simbolių paprastas lygiavimas susigadina).

Outputo pavyzdys:
``` shell
  
Žodis              Pasikartoja         Eilutėse
--------------------------------------------------------------------------------
Danius              8                   9 9 11 11 11 13 13 19 
apie                2                   9 9 
atsispindėjo        2                   7 17 
buvo                2                   7 7 
ežero               3                   9 11 13 
ir                  13                  7 7 9 9 9 11 11 11 11 11 13 17 27 
```

## Darbo išvados:
**C++ kalboje sunku dirbti su lietuviškomis raidėmis**

Programos paleidimas:
1. Atsisiųsti releas'ą
2. Atsisiųsti ir isidiegti C++ kompiliatorių (pvz GNU)
3. Atsidaryti terminalą toje atsisiųsto failo vietoje ir įrašyti komandą make 
4. Rašyti ./main arba main.exe (jei Windows)

