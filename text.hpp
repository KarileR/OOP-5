#ifndef text_hpp
#define text_hpp
 
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <iostream> 

using std::string;
using std::multimap;
using std::left;
using std::setfill;
using std::setw;
using std::endl;
using std::cout;


class Tekstas
{
    private:
        std::multimap <string, int> visi_zodziai;   //string name // line number
        std::map <string, int> dublicate;
        std::set <string> url;

        
        int WordsSk;
        int LinesSK;

    public:
        Tekstas(): 
            WordsSk(0) {};
        
        std::multimap <string,int>::iterator it;
    
        void insert_word(int lineNR, string zodis)
        {

            if (std::regex_match (zodis, std::regex("^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$") ))
                url.insert(zodis);
            else
            {

                if (zodis != "—" && zodis != "(" && zodis != ")" && zodis != "-" && zodis != "," && zodis != "." && zodis != "/"
                && zodis != "/" && zodis != "@" && zodis != "!" && zodis != "{" && zodis != "}" && zodis != ":" && zodis != ";"
                && zodis != "+" && zodis != "#" && zodis != "?" && zodis != "|" && zodis != "]" && zodis != "[" && zodis != "%"  
                && zodis != "^" && zodis != " ")
                {
                    clean_string(zodis);
                    sumazinti(zodis);
                    visi_zodziai.insert(std::pair <string, int> (zodis,lineNR));
                    dublicate[zodis]++;
                }
            }
        }  

        void clean_string(string &zodis)
        {
            char chars[] = "—()-,./?~`!@#$^&*()_+][}{|:;“„";
            for (int i = 0; i < strlen(chars); ++i ) {
            zodis.erase( remove(zodis.begin(), zodis.end(), chars[i]), zodis.end() );
            }
            //zodis.erase (std::remove_if (zodis.begin(), zodis.end(), ispunct), zodis.end());
        }

        void isvesti_zodzius()
        {
            std::ofstream out("zodziai.txt"); 
            for(it = visi_zodziai.begin(); it != visi_zodziai.end(); ++it)
            {
                // std::cout << it->first << "  ";
                // std::cout << it->second << std::endl;

                out << it->first << "  ";
                out << it->second << std::endl;

                cout << "Isvesti visi zodziai faile: " << "'zodziai.txt'" << endl;
            }
        }
        
        void CountWords()
        {
            for(it = visi_zodziai.begin(); it != visi_zodziai.end(); ++it)
            {
                WordsSk = WordsSk + 1;
            }
        }

        void set_Line_number(int n)
        {
            LinesSK = n;
        }
        int get_Line_number()
        {
            return LinesSK;
        }

        int get_Total_words()
        {
            CountWords();
            return WordsSk;
        }

        void sumazinti(string& word)
        {
                if(isupper(word[0]))
                {
                    word[0] = tolower(word[0]);
                }

        }
    
        void isvesti_URL()
        {
            std::ofstream out("url.txt"); 
            for(auto it = url.begin(); it != url.end(); ++it)
            {
                out << *(it) << std::endl;
            }
            std::cout << "Isvesti visi url faile: " << "'url.txt'" << endl;
        }
        
        void isvesti_pasikartojancius()
        {

            std::ofstream write("Cross_reference.txt");

            write << left << setfill(' ') << setw(19) << "Žodis";
            write << left << setfill(' ') << setw(25) << "Pasikartojimų sk.";
            write  << "Eilutės numeris";


            const std::string bruksnys(60,'_');
            write << endl;
            write << bruksnys << endl;
            
            for(auto it = dublicate.begin(); it != dublicate.end(); it++) 
            {
                if (it->second > 1) 
                {
                    write << left << setfill(' ') << setw(19) << it->first;
                    write << left << setfill(' ') << setw(25) << it->second;
                    for (auto it2 = visi_zodziai.begin(); it2 != visi_zodziai.end(); it2++)
                    {
                        if (it->first == it2->first) 
                        {
                            write << it2->second << " ";
                        }
                    }
                    write << std::endl;

                }
            }
            cout << "Isvesti visi pasikartojantys zodziai faile: " << "'cross_reference.txt'" << endl;


        }

};


#endif