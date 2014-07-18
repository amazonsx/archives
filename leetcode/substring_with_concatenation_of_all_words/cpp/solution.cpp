#include <iostream>
#include <map>
#include<string>
#include<vector>
#include <unordered_set>
#include <sys/time.h>
#include <unordered_map>
#define DEBUG
#define DEBUGTIME
using namespace std;

int loopcount = 0;

class Solution {
private:
    bool searchForward(const string &s, int start, unordered_set<int> &unmatchedRepo, 
        const int &wordLen, map<string, int> &dict, int totalLen, 
        map<int, int> &nextMap, map<int, vector<string> > &repoMap); 
public:
    vector<int> findSubstringBruteForce(string s, vector<string> &L);
    vector<int> findSubstring(string s, vector<string> &L);
};

vector<int> Solution::findSubstring(string s, vector<string> &L){
    vector<int> res;
    if (L.size() == 0)  return res;
    unsigned int wordLen = L[0].size();
    unsigned int totalLen = L.size() * wordLen;
    map<string, int> dict;
    for ( unsigned int i = 0; i < L.size(); i ++) 
        dict[L[i]] ++;
    for ( unsigned int i = 0; i < wordLen; i ++) {
        int start = i;
        int current = start;
        string concatenation(""), headStr("");
        map<string, int> currentDict;
        while ( current <= (signed)(s.size() - wordLen + i)) {
            if( (current + totalLen) > s.size())  break;
            headStr = s.substr( current, wordLen);
            if(dict.find(headStr) == dict.end()) {
                concatenation = "";
                current += wordLen;
                currentDict.clear();
                continue;
            } else if (concatenation.size() == totalLen) {
                string tailStr = s.substr(current + totalLen - wordLen, wordLen);
                string formerHead = concatenation.substr(0, wordLen);
                if (formerHead == tailStr)  {
                    concatenation = concatenation.substr(wordLen);
                    concatenation += tailStr;
                    currentDict[formerHead] --;
                    currentDict[tailStr] ++;
                    res.push_back(current);
                    current += wordLen;
                } else if(dict.find(tailStr) == dict.end()){ //not contianed in L
                    concatenation = ""; 
                    currentDict.clear();
                    current += totalLen;
                } else {
                    unsigned int j = 0;
                    for( ; j < concatenation.size(); j += wordLen) {
                        if (concatenation.substr(j, wordLen) == tailStr) {
                            break;
                        }
                        currentDict[concatenation.substr(j, wordLen)] -- ;
                    }
                    concatenation = concatenation.substr(j + wordLen);
                    concatenation += tailStr;
                    current += j;
                }
                continue;
            }
            // concatenation is still not enough
            while( concatenation.size() < totalLen )  {
                if (concatenation.size() == 0) {
                    if (dict.find(headStr) != dict.end()) {
                        concatenation += headStr;
                        currentDict[headStr] ++;
                    } else break;
                } else {
                    string tailStr = s.substr(current + concatenation.size(), wordLen);
                    if (dict.find(tailStr) == dict.end()) {
                        current += concatenation.size() + wordLen;
                        concatenation = "";
                        currentDict.clear();
                        break;
                    } else if ( currentDict[tailStr] == dict[tailStr]) {
                        unsigned int j = 0;
                        for( ; j < concatenation.size(); j += wordLen) {
                            if (concatenation.substr(j, wordLen) == tailStr)
                                break;
                            currentDict[concatenation.substr(j, wordLen)] --;
                        }
                        concatenation = concatenation.substr(j + wordLen);
                        concatenation += tailStr;
                        current += j + wordLen;
                        break;
                    } else {
                        concatenation += tailStr;
                        currentDict[tailStr] ++;
                    }
                }
            }
            if (concatenation.size() == totalLen) {
                res.push_back(current);
                current += wordLen;
            }
        }
    }
    return  res;
}

bool Solution::searchForward(const string &s, int start, unordered_set<int> &unmatchedRepo, 
        const int &wordLen, map<string, int> &dict, int totalLen, 
        map<int, int> &nextMap, map<int, vector<string> > &repoMap) {
    if (unmatchedRepo.find(start) != unmatchedRepo.end())
        return false;
    if ( (start + totalLen) > (signed)s.size()) {
        //unmatchedRepo.insert(start);
        return false;
    }
    bool flag = false;
    map<string, int> tmp_dict;
    int next = start, leftLen = totalLen; 
    if (nextMap.find(start) != nextMap.end()) {
        next = nextMap[start];
        for ( unsigned int i = 0; i < repoMap[start].size(); i ++) {
            tmp_dict[repoMap[start][i]] ++;
        }
        leftLen -= wordLen * repoMap[start].size();
    }
    string currentStr("");
    vector<int> accessed;

    while(tmp_dict != dict) {
        if (unmatchedRepo.find(next) != unmatchedRepo.end())
            break;
        if ((next + leftLen) > (signed)s.size()) { 
            //unmatchedRepo.insert(next);
            break; 
        }
        currentStr = s.substr( next, wordLen);
        if (dict.find(currentStr) == dict.end()) { 
            for ( int i = next; i > start; i -= wordLen ) {
                unmatchedRepo.insert(i);
            }
            break; 
        }
        if (tmp_dict[currentStr] > dict[currentStr])
            break;
        accessed.push_back(next);
        for (unsigned int i = 0; i < accessed.size(); i ++) {
            repoMap[accessed[i]].push_back(currentStr);
        }
        if (nextMap.find(next) != nextMap.end()) {
            // this if may will always be true!?
            if ((unsigned)leftLen >= (repoMap[next].size() * wordLen)) {
                for (unsigned i = 0; i < repoMap[next].size(); i ++) {
                    tmp_dict[repoMap[next][i]] ++;
                    leftLen -= wordLen;
                }
                leftLen -= wordLen * repoMap[next].size();
                next = nextMap[next];
            }
        }
        tmp_dict[currentStr] ++;
        next += wordLen;
        leftLen -= wordLen;
    }
    for ( unsigned int i = 0; i < accessed.size(); i ++) {
        // this if may will always be true!?
        if (next > nextMap[accessed[i]])
            nextMap[accessed[i]] = next;
    }
    if (tmp_dict != dict) {
        unmatchedRepo.insert(start);
    } else  flag = true;

    return flag;
}

vector<int> Solution::findSubstringBruteForce(string s, vector<string> &L) {
    vector<int> res;
    if (L.size() == 0)  return res;
    int wordLen = (signed)L[0].size();     
    int totalLen = L.size() * wordLen; 
    map<string, int> dict;
    for ( unsigned int i = 0; i < L.size(); i ++) {
        dict[L[i]] ++;
    }
    map<int, int> nextMap;
    map<int, vector<string>> repoMap;
    unordered_set<int> unmatchedRepo;
    for ( unsigned int i = 0; i < s.size(); i ++) {
        if((i + totalLen) > s.size())    break;
        bool flag = searchForward(s, i, unmatchedRepo, wordLen, dict, totalLen, nextMap, repoMap);
        if(flag) res.push_back((signed)i);
    }
    return res;
}

int main(int argc, char *argv[]) {
    Solution so;
    /*
    string s("barfoothefoobarman");
    string str_arr[] = {"foo", "bar"};
    */
    /*
    string s("amxbtipvhwzyytfnekijzdvutiweyhcyvbbqjqosonrmiwcoikxjpsfiacpbltbjudbfvpxkfqypoaeykbibwpkyrbzfubqqgrvbhunonmdbmhazlkahbmftnfajiqbohwpqtdegpkjdtlcevfnxttsjausikuytsnklsqtjcdnworcmyslsndbpzvzjrxekmqxfhrqlwfjkxowxgjptmsilqhwhebtsrtxakqoivxsulrsrajmpewcufbbjexexqbaarokplejzxbsanfprdtljwoualyybcydvonkzsuapxtpkagddcomydhbqfbsjzvfplpodlrujkkvkszpupcvulwlsxdcyahnlydqkulvexqqprgmhkhdvdopatrawanhzqajnletkwmzoslxeuazxrozkiziimqhfqqudwnntzojtcgzwiywzpvmzxuhjmrqejmjgaybbnkxrqwpaxlaojongkwrxnkdxwnfylgaaqztivjiuwkihaxnluhkjrninanoovoonpixmtghpsrzvrmgnvqwmfhcguqusgkfvsdhnlqdfkcabqiooamagteoqwiieupzpsjcfbhlllnmcwcswpseizsyvcgaxwbmqmoyqwlbjyqnwsfvhyzqzsowuxyrvafnouleswibxyptswoauqsviiscfqwcsbqhxbnravvxvksoghodziahqslyljaflsokwccwzxtvjnjrwzwvhxczrqxezakmsyxoabkcyfxjtiaphznqyppphnwhngtheswhtijtqiclqfcxepnchctorpvgxroejmlfwwymebzwgctmtiqcmlrebokahaetmryjnwxtzzphdktwulzhxsnaizaqafjowhxmfxhfwzmzlixgtwnqqcszbtrbaaqyjpkomuvktijgqhmlfbeydwzfrqirsaqbqcreynptxaapjmarogptdoawgjoyjgzbksgjhxcexcthpwyfcpahfbelmujvckzmcfvkcyqbckktikamzbweecpqwanakmmnrizvipxmbjglugytjwanyrdwsrwcdirxsqucitpldvxxdxqntscrkgnczjgctybmqwqarfmucjriikvbczsofhqeszjlxkzpiqqavewapoixafyeeqtkzlqrkzchmczwupypvvrklzhlefrlxkxwwnpgprqdvpbpgchbxynkyuxeborazoyxendvgvackbtsdavczimzclffaxfbndyrqdozzoblqwgvxbyykmzoyguafbbtfbmxgbwhpzthwbdvcdtopudnazngaqbfrnfaqdhidcpbdswgvrunnzapyqvziygcmlcerjmuocxrwvzuowhbvjqubovkmbmapofgzrcnvbhswgokcvnagfwitr");
    string str_arr[] = {"odlrujkkvkszpupcvulw","ybcydvonkzsuapxtpkag","lsxdcyahnlydqkulvexq","bjyqnwsfvhyzqzsowuxy","hzqajnletkwmzoslxeua","zpsjcfbhlllnmcwcswps","cufbbjexexqbaarokple","xakqoivxsulrsrajmpew","nluhkjrninanoovoonpi","auqsviiscfqwcsbqhxbn","fylgaaqztivjiuwkihax","eizsyvcgaxwbmqmoyqwl","hjmrqejmjgaybbnkxrqw","ravvxvksoghodziahqsl","zxrozkiziimqhfqqudwn","xmtghpsrzvrmgnvqwmfh","rvafnouleswibxyptswo","abqiooamagteoqwiieup","ddcomydhbqfbsjzvfplp","ntzojtcgzwiywzpvmzxu","jzxbsanfprdtljwoualy","wxgjptmsilqhwhebtsrt","qprgmhkhdvdopatrawan","paxlaojongkwrxnkdxwn","yljaflsokwccwzxtvjnj","cguqusgkfvsdhnlqdfkc"};
    */
    /*
    string s("cxksvbkmmlkwviteqccjhsedjmoyimskmeehhovubiszsodiqhtyaxdlktmuiggukldubzqdjiebyjkpqfpqdsepmqluwrqictcguslddphdyrsowjhbcnsqddmbvclzvqhsksxnhethvnyuxfxzsqpxvdasflscbzumssbbwuluijqhqngkfxhdahvhunjwpgkjylmwixssgizyyhifepigyenttyriebtcogbwftqmcpmcwvhcmsklyxgryxccyvhodiljbbxftjhrerurleejekacheehclvfviqxmnefzowdhswsxcbdmdfvilekzcrukityxyfwmcctwanvdoyptfnbtrnsthoepieoiklwmppkpegssgknmxpfoezilnocxsrfcebqtsdkwjfqppedmvkczjmnzcpwxiebofujyxuwgzpxotdcqnerzteyvwwseauvgoeglyctzrspmvrcjyuiraimwehdfbalretcfxxeppwdnniwnegeeotdsaixdikuodytbxasmwxzlfxzldfstaxmcflfpybdbzzewzylxwmidkjrprjjtgxwnideifjkeiqdjpogncrsmcjetsnnamlpwotftdranhdxytfnvwgkzroukdjmpucnjxscajcqtfptaujwtrguiwouzyhqulddiygjjkbesqyskjofawzisqdrqkjkvnodlwowgrbyhzruihzkezsyrvshhbreqhkbfaymsbmzaftkpvutwotnklutnnydxihcihqcidckkxwzssuogodszzmopmumwbogkhjukleukcufuqvcezxgylunxobvrsbbzkvlxbhiddnzuieyhbeimbxlpzghthksugdrjkznoomkzsiitpqhqquhraqkkbcgjhxstzhjpwtoocxirprjfmqwmhgyikgtrellftwupqldsinlzfwfrmdfvmgfwmyqsmdxhzuwpfbjprwowsvphzuelckjrkbjwejdgdbxkdhzwfnsaljjkdnxixizikigqrmwwnugsdhokxikirtuxjtfibgslozeilagywptbwhmvqwdjszgbsnjutchkdluooaompjooraljypusobvjohdklmuqyogoquaigqwxsjiryclpfjywsdgdpctpqzdivgqbwoapykiypvpuepswsybkcwzsxfbvntylibcglmeciuzojrnesqounppmwshjlgxtjzzumgzwcymlpbrjsfehxtttldfwlcsudrqpzpnbnapfbgovoucnnygadnzqrrkvkckkuanjaeodnfzbzdqpdypgmoydhiysnlehnrsnwjsloropxeeacwjomhuusuohhsqulihjrcuhvixsmdvpbefqnbmhwaodueafnjpellmhulbiqwzscfiqiuxgwomqsmxfvmmhyaqunrcdocvqjfirbiyzwmpoypwtdkcdksxzkacaeasnhbgjlgkhsaxqrvmufoyrjxqvztxdvpscszndfymaamqrhelnvleejxbiqyonpgpihdnpbcpbohuvmfkhtrncoqmgqatfjkpqnffqjutxenuqvhzoyosogeuwhpdqzvipaofjkbiooeejlfzjvrzbytxhidxkyfzavglghtuyzbhlgjwcawdardhcigmgonijvtpdokdnlmatvzxyvdymggqqmcyargmnbbqpnveahhudgtbdwzrehiuwmsyeykrbojqbexelgaomtrrqtiucspyfhxjijajxjcbpbfahfrvyimodwjgpyewhdfrphbmsfnhguhpzakalyoowzunzbjhgqyvxbkrgzyouidtinttnkkkjezjhjsqbslzuvqcvrrrzwkjkgdzsnldtlmdwgtxzewvcpxzgqqhncqzkvackmgexujtbcqcipxmgwlopdvcgndqjdvtpbzoxijamacvrzjxyvnnykpgxuxixucpvddumpvapxxizhhxeukcebjdvimucqjztpvheqivqfdpokosgyxkbipwsbqurcvltquzjcwzkzqyletteqffaubswtonxjasbvrkznljodkbhfunvzsxwvpsrdhqokjpfcceqnqgrckaheoegibceqwvvdljnwyuzcbrsrxlthlcobgwkhyqzwlubyfrvflwimnafknauacickeoteeucrodrvuobikjwxlckyeeyjoctusnawhcpyfhtcvukifgfskpspvrylvtfogfmqhcqpjlrgidopjwiunalltjwpccflhrdrvtgegznocdgnzohposakdwbgagtkxwbtrjzxkoomuuzvkjkadkkhjlpjtittewoxfpwpemdygftsqgttqfcbtrlmbefhbteijbapnfpwkkqcslwjramkuxyveeffzlpkopbevsahdskveigvivhesfcwlhdnstxhkblhtnpyfbwljegrzpysxaqihwxzrxibyvjriasqbobmskfsbdmydejkagmrdutdqevagpsjduvxgarhefihkrukzgcdcxguddvlsnuxjrxrrozvuhfgazqzhuejtlgyqdllsfiewhvqwunsdsydtqfanjmiwujpxuapcktysrqoleirwiwsabupngajcjyzdarflmgddwtradizletninfvwfgyohathrbsdhxjfsaivkjiqcyypdvniemylmrufspkbmthhvpcfanwclwtouhwavunjnhogwyhluqsphwxhjvjutfkpoipjecusmiaiijvcapujmrrxocshhexxnmgrraldklntxlxzarimkzkyceglkfjxtrrkucpeqfznqxmqqufbwrbaxhnhoyfiqwumakqsrsfhrtzhqekoxmouvdckchsufmghyyarqhyhbartebhenxylaavcjnwobeycdytthudiuudavkeljdwkdtopindjrdnudjqlftvznzbklgxvlthqmvfuklgcovysgodlhakwzmjnugifcpvqmbnzovdcqbwzsbkbcvydjhqdpakrphkeixdwuibmjxlbzwddtdgcmxhbxtvpafvleajyikkrkyvluaondwrptastvnivufiafsanengqldbfdrugonxjnqckfkfcrocwiflosufdxikbaejqthzgzcqeoxggnlexqqmkktpjbzkbfwtydtgcvyilxrrlewkwowgapvjruwubsozxjhzgfjrcalpejaazyizodihzedaytbveiwkpgesgphnajpziyyybihdpkfnghlkrhvhnzbwqkjquareyrcczjfqvkebtpmnyjwmkxkajvsfvljucnwbybsunyxjplwnusbgrlicgaieltynjwrhzlbmlzvamtphntngeyjnytrmorbxnufmfiasjwswrkdfdsljqwwrppfgggdtdkhktidcgxyxhdcmyqwqosjekomqxpmaatkvbpxhnyhwdljdbfuszfwjukctzovbjhwnxwwkwdgzppdswzkweihasjtuzoxjywwvsuhoynppfujdvwzaghcbsyxsoubmqzhitoyteqklmwoisqkaxmbpkyhztklllvwhjuapmnazjrhbhrbgffvqdfryrckdzgkjcmapzdqiuzldspjxugpxlgydliikouvsgyjgbzqxacasrjslphkdqiidsqniklbsjkymmpjmtlfkuxxlghowsyzkopvaawtlitzukijdtqppnoavyrsqptcgixgkvbxgxwcjglpzbeqqvrmtigjzbnfknowkrwqostybgnaktraokohuwstyibkvpihgeyxztvabkcldvosfcbbbuxzcajzptgxygwzbrzddbohzcbgheiiyhhchsdylmvlsukuljxrnnymqbsxfchgjoksiqqtcohwirqvdpmsfmevpyuxbbdmrpfzfvujldgtvypaqdsvqwsfwoczrhmiztjgqfqcjyvewmeoqwjiudnqrssizesazdhpjxrsxpytdektctbwzroslgbmmvnlzubitucqjalnevigrmeqfuiqblcnhrbilcqgyuwiukxafhgwtmoagxqhkvxtmabaetgcnfkjpjjurrtmdhnkgfttasmpuqpyjxbzcnirxsoojjcpspbbvuuxpimjydikbjjdwrxvlnlvwokqflrchlaywokussetdnybhxzsmkpkybbgosiwgiwcxgwradmfsmhzkguwsjhtlizbchziswmrcjifowkgitisbcrunanakocmxbxpxjicushiotpxnxrobikoixpunrhlsgcsrlwmdfusylplkgclrmcbkrwzkfkelnyeyuqdznvyamllvnymacnmvllfqymdlkilfaognmgqysbvfbjhextbkhhdftgsfqdmrttgfbwgtzdbdnijmekwntzsoikuypiridaqfyyaybbdommasyxfsyxggjchylyiqayvzywxazcolordookgmhpvstcqgcbxdzseaqbaqfqdvhjjvtqkbhhtajmhnneqoyuopxqhehkzotjmnbyqiflkoztdmzwdaqtpqkyuriwhefvtgtjqywcowyskxonxghoytovmxrtdypwgihyjdazzytkyjzxqioqbcnnbgheeyakihitnltmlmyjwyjogxeizuxbaghfeirprcienbtyqrkmrvaasgktchwdoekuobjffsmsvftlyfxqazquiankjkpxozucddjixxdtcweddevffnznpoayypyopssuxecxbfqgdwjgaglgtmvibvibngseakyaqaxuipalllsorfwksrutpcuelminzgnriklqzlcnwwbpbxzvqvohylllztyaboskadccrgppcsfgrgbhcsrcfcngynhbbbncgqexyvpbnujeamneeegljtsjhbkkcamissiqnxrarcetpsyvyehhabqjcbtgdiovawlqtfqmhxgwrgupmdxoepxistovdeqfdcvyhmloltnczhrnkqcqgzayuquxumfzoayxolozeddfkxswnuovwowqeqqaevctxasmlgnpjrwvootdjhzhxvzdnpgrmimmifavnnkxgiuwwoahxbovwqalhgcworiwyitlxdkenfakvatsbkpzaqkhwpdnillgvfrtkexyjzigcdydnqfpgrxegcroqduliogssfqdfalhglmtbrjjjiormhgckcqsswnmcfrhgcqoochrusbfcrwpyerjjhdbgsqiyhrgmhucjdtfwwmanjpopjxasceyvugvdzbpgvtsapxwlkzbvopmxonqsrqplxkqwlgfibxjquheggfdxwqwmfoewfujegzcuhhclenbbxfjfmncifbumpbiuxtadudxekcprrquqyfwksatzbpltsvnpqovltspdwgwqysgwyehsfcsitfbmdrdthygatxfrdchcuoysshlzlfifmltpcyljxrlsprjuttwpjxkbexdsenzqysidqtopmajbrvwmoudxrpaymdqsspjtjtwbomtameefzctpwxoqmpobugtnxeiizelnqeofjskkugasdoirfyucgqpfuznudzjvfxaqrnbntdiyrqrzrmbxcsdyrsuwterzdurxjskcvscpltqchrbjlgkczgyumrtqlnnufzyduauhwklddmpotbsuhsoulkmxxbtcauhwwbdsnqysdniyoasvugrgqdfneashubftdjnsblneyvcoyumsddatjhjnidueeaxjllemyrtxmxnkszfxfhqopbbxeydladunoybopwlcubooavlfddvsfxrlxuwzxrmnrpchmpliqbwtxhyckuuptldshzrfsfukwwtiogqehoxgvyigucxppahzcygwfaibzbmnjetrttzoriwnmucewldaljxqjfrkjdxsitldmlrfvoshkwnghqhszgilnbvwhvrroeuaplhmbzulxhueabybjimwjkvqhmjvqdxireuufqgcaaiadgbmoqkzafshtbemhduahquohasjcajfimryccxejpndtrpcwlcdbwtkzltbnchxpavtevyqmltffkjbvlhwkajjocmdhvbywyrctpsidnpixzlsksrwvaflcuojprhlqbqlqivtwldtkpowjftefaphugtkxcxpdndwyyrujvpvmdsxklcpntzibusbwpqcdvybupxfmobautyegcwtxvbzpvanlspqoptkhspviswclwjtafnxcqytmaiztarjpmtygkuodstqockqjznnpmgdmqehqxqgjlgrwagbuzrkdbaocobscjxqzeyqbqynegechmddnuosyogaejuiuuzuyzmzrmovutxbfchvzvnzjuzqfwyaqxwqykrqygnsznwgpddoyrnjnpzsnysdxqvyamqysdttqpcgsfwswkbjzdemdyrcpoaraqstulomcquuwroudrgcumqzkjcbxctzvlsryhdazawxrksubayy");
    string str_arr[] = {"otftdranhdxytfnvwgkzroukdj","iflkoztdmzwdaqtpqkyuriwhef","lbsjkymmpjmtlfkuxxlghowsyz","cddjixxdtcweddevffnznpoayy","snjutchkdluooaompjooraljyp","fuszfwjukctzovbjhwnxwwkwdg","frmdfvmgfwmyqsmdxhzuwpfbjp","ukityxyfwmcctwanvdoyptfnbt","mhnneqoyuopxqhehkzotjmnbyq","vtgtjqywcowyskxonxghoytovm","wouzyhqulddiygjjkbesqyskjo","mfiasjwswrkdfdsljqwwrppfgg","zruihzkezsyrvshhbreqhkbfay","rsxpytdektctbwzroslgbmmvnl","jdwrxvlnlvwokqflrchlaywoku","xhnhoyfiqwumakqsrsfhrtzhqe","gtbdwzrehiuwmsyeykrbojqbex","tpcyljxrlsprjuttwpjxkbexds","tsjhbkkcamissiqnxrarcetpsy","keiqdjpogncrsmcjetsnnamlpw","rquqyfwksatzbpltsvnpqovlts","tdgcmxhbxtvpafvleajyikkrky","qvrmtigjzbnfknowkrwqostybg","vluaondwrptastvnivufiafsan","rnsthoepieoiklwmppkpegssgk","cyypdvniemylmrufspkbmthhvp","ihcihqcidckkxwzssuogodszzm","chrusbfcrwpyerjjhdbgsqiyhr","wmeoqwjiudnqrssizesazdhpjx","ommasyxfsyxggjchylyiqayvzy","kwntzsoikuypiridaqfyyaybbd","cwjomhuusuohhsqulihjrcuhvi","wxazcolordookgmhpvstcqgcbx","nusbgrlicgaieltynjwrhzlbml","xrtdypwgihyjdazzytkyjzxqio","xfvmmhyaqunrcdocvqjfirbiyz","fuklgcovysgodlhakwzmjnugif","hzhxvzdnpgrmimmifavnnkxgiu","xsmdvpbefqnbmhwaodueafnjpe","xfbvntylibcglmeciuzojrnesq","cnhrbilcqgyuwiukxafhgwtmoa","xkajvsfvljucnwbybsunyxjplw","zuieyhbeimbxlpzghthksugdrj","gbzqxacasrjslphkdqiidsqnik","jxtrrkucpeqfznqxmqqufbwrba","chziswmrcjifowkgitisbcruna","jyzdarflmgddwtradizletninf","pcktysrqoleirwiwsabupngajc","dkenfakvatsbkpzaqkhwpdnill","kbiooeejlfzjvrzbytxhidxkyf","wlopdvcgndqjdvtpbzoxijamac","xsoojjcpspbbvuuxpimjydikbj","faubswtonxjasbvrkznljodkbh","uqsphwxhjvjutfkpoipjecusmi","nawhcpyfhtcvukifgfskpspvry","xkdhzwfnsaljjkdnxixizikigq","zxgylunxobvrsbbzkvlxbhiddn","alltjwpccflhrdrvtgegznocdg","gffvqdfryrckdzgkjcmapzdqiu","hzedaytbveiwkpgesgphnajpzi","wmpoypwtdkcdksxzkacaeasnhb","hsdylmvlsukuljxrnnymqbsxfc","bbbncgqexyvpbnujeamneeeglj","bjhgqyvxbkrgzyouidtinttnkk","pyuxbbdmrpfzfvujldgtvypaqd","cfanwclwtouhwavunjnhogwyhl","plkgclrmcbkrwzkfkelnyeyuqd","ugvdzbpgvtsapxwlkzbvopmxon","msbmzaftkpvutwotnklutnnydx","pdwgwqysgwyehsfcsitfbmdrdt","elgaomtrrqtiucspyfhxjijajx","biqyonpgpihdnpbcpbohuvmfkh","llmhulbiqwzscfiqiuxgwomqsm","mpucnjxscajcqtfptaujwtrgui","gdzsnldtlmdwgtxzewvcpxzgqq","gdtdkhktidcgxyxhdcmyqwqosj","zubitucqjalnevigrmeqfuiqbl","aymdqsspjtjtwbomtameefzctp","kjezjhjsqbslzuvqcvrrrzwkjk","zavglghtuyzbhlgjwcawdardhc","fawzisqdrqkjkvnodlwowgrbyh","vrzjxyvnnykpgxuxixucpvddum","rdutdqevagpsjduvxgarhefihk","ydhiysnlehnrsnwjsloropxeea","hgjoksiqqtcohwirqvdpmsfmev","jyxuwgzpxotdcqnerzteyvwwse","sozxjhzgfjrcalpejaazyizodi","usobvjohdklmuqyogoquaigqwx","tmdhnkgfttasmpuqpyjxbzcnir","quareyrcczjfqvkebtpmnyjwmk","rmwwnugsdhokxikirtuxjtfibg","qsrqplxkqwlgfibxjquheggfdx","rukzgcdcxguddvlsnuxjrxrroz","oomuuzvkjkadkkhjlpjtittewo","wqwmfoewfujegzcuhhclenbbxf","yjogxeizuxbaghfeirprcienbt","qbwoapykiypvpuepswsybkcwzs","lvtfogfmqhcqpjlrgidopjwiun","rwowsvphzuelckjrkbjwejdgdb","jfqppedmvkczjmnzcpwxiebofu","hygatxfrdchcuoysshlzlfifml","gxqhkvxtmabaetgcnfkjpjjurr","zppdswzkweihasjtuzoxjywwvs","hgyikgtrellftwupqldsinlzfw","kckkuanjaeodnfzbzdqpdypgmo","aiijvcapujmrrxocshhexxnmgr","sjiryclpfjywsdgdpctpqzdivg","kuxyveeffzlpkopbevsahdskve","uqvhzoyosogeuwhpdqzvipaofj","gjhxstzhjpwtoocxirprjfmqwm","cwiflosufdxikbaejqthzgzcqe","qeqqaevctxasmlgnpjrwvootdj","ymggqqmcyargmnbbqpnveahhud","ekomqxpmaatkvbpxhnyhwdljdb","zvamtphntngeyjnytrmorbxnuf","uhoynppfujdvwzaghcbsyxsoub","efhbteijbapnfpwkkqcslwjram","koxmouvdckchsufmghyyarqhyh","tthudiuudavkeljdwkdtopindj","nwwbpbxzvqvohylllztyaboska","dccrgppcsfgrgbhcsrcfcngynh","qdpakrphkeixdwuibmjxlbzwdd","ftgsfqdmrttgfbwgtzdbdnijme","ounppmwshjlgxtjzzumgzwcyml","cpvqmbnzovdcqbwzsbkbcvydjh","pbrjsfehxtttldfwlcsudrqpzp","qbcnnbgheeyakihitnltmlmyjw","ztvabkcldvosfcbbbuxzcajzpt","xfpwpemdygftsqgttqfcbtrlmb","hncqzkvackmgexujtbcqcipxmg","ilfaognmgqysbvfbjhextbkhhd","hvqwunsdsydtqfanjmiwujpxua","yqrkmrvaasgktchwdoekuobjff","egeeotdsaixdikuodytbxasmwx","jfmncifbumpbiuxtadudxekcpr","slozeilagywptbwhmvqwdjszgb","kkugasdoirfyucgqpfuznudzjv","pvapxxizhhxeukcebjdvimucqj","bqurcvltquzjcwzkzqyletteqf","cbrsrxlthlcobgwkhyqzwlubyf","mqzhitoyteqklmwoisqkaxmbpk","nbnapfbgovoucnnygadnzqrrkv","ztpvheqivqfdpokosgyxkbipws","auvgoeglyctzrspmvrcjyuirai","yhmloltnczhrnkqcqgzayuquxu","funvzsxwvpsrdhqokjpfcceqnq","vuhfgazqzhuejtlgyqdllsfiew","gmhucjdtfwwmanjpopjxasceyv","vpscszndfymaamqrhelnvleejx","dzseaqbaqfqdvhjjvtqkbhhtaj","zylxwmidkjrprjjtgxwnideifj","nzohposakdwbgagtkxwbtrjzxk","igvivhesfcwlhdnstxhkblhtnp","trncoqmgqatfjkpqnffqjutxen","vwfgyohathrbsdhxjfsaivkjiq","rdnudjqlftvznzbklgxvlthqmv","kopvaawtlitzukijdtqppnoavy","raldklntxlxzarimkzkyceglkf","nakocmxbxpxjicushiotpxnxro","wxoqmpobugtnxeiizelnqeofjs","smsvftlyfxqazquiankjkpxozu","fwksrutpcuelminzgnriklqzlc","nefzowdhswsxcbdmdfvilekzcr","ibvibngseakyaqaxuipalllsor","znvyamllvnymacnmvllfqymdlk","gcvyilxrrlewkwowgapvjruwub","mwehdfbalretcfxxeppwdnniwn","wwoahxbovwqalhgcworiwyitlx","nmxpfoezilnocxsrfcebqtsdkw","engqldbfdrugonxjnqckfkfcro","grckaheoegibceqwvvdljnwyuz","jcbpbfahfrvyimodwjgpyewhdf","rvflwimnafknauacickeoteeuc","gxygwzbrzddbohzcbgheiiyhhc","wcxgwradmfsmhzkguwsjhtlizb","bikoixpunrhlsgcsrlwmdfusyl","ssetdnybhxzsmkpkybbgosiwgi","vyehhabqjcbtgdiovawlqtfqmh","opmumwbogkhjukleukcufuqvce","vjriasqbobmskfsbdmydejkagm","gjlgkhsaxqrvmufoyrjxqvztxd","yyybihdpkfnghlkrhvhnzbwqkj","kznoomkzsiitpqhqquhraqkkbc","yhztklllvwhjuapmnazjrhbhrb","jjiormhgckcqsswnmcfrhgcqoo","rphbmsfnhguhpzakalyoowzunz","igmgonijvtpdokdnlmatvzxyvd","rsqptcgixgkvbxgxwcjglpzbeq","zldspjxugpxlgydliikouvsgyj","enzqysidqtopmajbrvwmoudxrp","naktraokohuwstyibkvpihgeyx","zlfxzldfstaxmcflfpybdbzzew","mfzoayxolozeddfkxswnuovwow","rodrvuobikjwxlckyeeyjoctus","yfbwljegrzpysxaqihwxzrxiby","croqduliogssfqdfalhglmtbrj","gvfrtkexyjzigcdydnqfpgrxeg","xgwrgupmdxoepxistovdeqfdcv","oxggnlexqqmkktpjbzkbfwtydt","pyopssuxecxbfqgdwjgaglgtmv","svqwsfwoczrhmiztjgqfqcjyve","bartebhenxylaavcjnwobeycdy"};
    */
    /*
    string s("lingmindraboofooowingdingbarrwingmonkeypoundcake");
    string str_arr[] = {"fooo","barr","wing","ding","wing"};
    */
    /*
    string s("a");
    string str_arr[] = {"a"};
    */
    /*
    string s("aaa");
    string str_arr[] = {"a", "a"};
    */
    /*
    string s("abababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababababab");
    string str_arr[] = {"ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba","ab","ba"};
    */
    string s("abababab");
    string str_arr[] = {"a", "b", "a"};
    vector<string> L(str_arr, str_arr + sizeof(str_arr)/sizeof(string));

    struct timeval first;
    gettimeofday(&first, NULL);
    vector<int> res = so.findSubstring( s, L);
    struct timeval second;
    gettimeofday(&second, NULL);
    cout << "The total string size is " << s.size() << endl;
    cout << "Total dict size is " << L.size() << endl;
    cout << "Total time is   " << 1000000 * (second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;

    for ( unsigned int i = 0; i < res.size(); i ++) 
        cout << res[i] << "    " ;
    cout << endl;
	return 1;
}
