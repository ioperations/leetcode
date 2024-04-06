// Given a string s, partition the string into one or more substrings such that
// the characters in each substring are unique. That is, no letter appears in a
// single substring more than once. Return the minimum number of substrings in
// such a partition. Note that each character should belong to exactly one
// substring in a partition.

use std::collections::{HashMap, HashSet};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn partition_string(s: &str) -> i32 {
        // 2 <= s.length <= 105
        // s consists of only English lowercase letters.
        fn my_impl(s: &[char], cache: &mut HashMap<Vec<char>, i32>) -> i32 {
            if s.is_empty() {
                return 0;
            }

            if s.len() == 1 {
                return 1;
            }

            if let Some(&v) = cache.get(&s.to_vec()) {
                return v;
            }
            let mut hs = HashSet::new();
            hs.insert(s[0]);
            let mut ret = i32::MAX;

            for (index, &value) in s.iter().enumerate().skip(1) {
                if hs.contains(&value) {
                    // this substring is not allowded anymore
                    let z = my_impl(&s[index..], cache);
                    ret = ret.min(z + 1);
                    break;
                }

                hs.insert(value);
                // let z2 = my_impl(&s[index + 1..], cache) + 1;
                // ret = ret.min(z2);
            }
            cache.insert(s.into(), ret);
            if ret == i32::MAX {
                return 1;
            }
            ret
        }
        let mut hashmap = HashMap::new();
        my_impl(&s.chars().collect::<Vec<_>>(), &mut hashmap)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "abacaba";
        let output = 4;
        let ret = Solution::partition_string(s);
        assert_eq!(output, ret);
        // Explanation:
        // Two possible partitions are ("a","ba","cab","a") and
        // ("ab","a","ca","ba"). It can be shown that 4 is the minimum
        // number of substrings needed.
        //
    }

    #[test]
    fn case2_test() {
        let s = "ssssss";
        let output = 6;
        let ret = Solution::partition_string(s);
        assert_eq!(output, ret);
        // Explanation:
        // The only valid partition is ("s","s","s","s","s","s").
    }

    #[test]
    fn case3_test() {
        let s = r###"axuzwxhwtrxaudbfecdagodjvyovokjfpnrecdypzrmdchgcdzmwgdfmnichtlttldfwumrzexkqhwkifiqsmqipuaacmjvysg
iungrgwbzimdlmlbrkaziabwusryijthqslpqohdkifzwyyeaqqttmudbfrwguicbpjmwksqxveginxaoauypfkdtjmbvkcowkjis
qajxfeiigpkhxilhphytykjmhhzcxdsrylmrfxevboxcmtbnwllcgzrpnyilnuidoydjisnietdxsdpeqgkphllzyaccxwingadfn
ilfprytsbmlimzlkbyscepbtdpnloegxssmytqqyttpriyjpnwnikviufqbgririqsjongvoslyxtlnkejimqbpjcvlnjfyqncirt
qesisrscxtwhqbzueaobqzhkbepkvoampcqocjfljwcuhkoltwzdashpxhdwsiuijzgbciqwrmxdxwrnqhhzwqhbzvjboibegvytj
acieucwjqifmhkpcwmjttlnzqvpyldiimshxzqlqvavdgriurvlyrwnvowyobprafqznijgmjwfkezpcaeczvvysqjelfvrxqrvqf
xkclzvtmxxtealraoyctfogxdvdlfzvmdmpctplkkaxxvcsfitebxdzxftvuedojsxrzcyrgsoihsmfjvmasxhdpyjkthygnfvhye
xujbqxgpcxphobklshkoorfupvufyudcejqitvedzdfaunujsbankcpevhkbzafhcfepulitogxtytrptorxinmwxuhrlvfrghujg
xyzqlidfqwtulwkltbonrbggeqkiiugvjsxwwcxwfozswpmmcmpbadlglabavkiorcmdyfqmmyjekjydzoddsadhhcyjlrmqcxckq
icxkwxgnffxulabiwqqjpjzpyghfxeumbbizptjmnfkuwliojhmcmbwrohjafflnlubjaiyghshouenwgkpfkfnrxziygtztrtacj
kyyedwwcpkogtcenekdwibfielpswyhgadmbelgppmvlqyxecoruanrdpuxquebdumtkivcbaaypqoqecuuzksceijmarccrefqkc
qhvapscqjmkqzmwkbnfmcmzxsjdgcmfekkfmjbkccrqhrcztkkczyfvuezvrtpnlklyhxdhdntsuuhvrploclujnthwttufwvbyqs
loruvsdnywerqdqsoffoounqoumsugbaesbqhbxzuvpwvrbuhfrqjnbywqzaxkgzuoyczfprpewhfeqiachnnjmyvdtnioesvuyfn
zuwtaclsaumdfpwokapqxkvvfpkasnxknghmuthcmzhiyeizajjklytaagcbonwukrwulcqsmbdypggciadxezatppksidnemrikn
ylcwnyvaxtwmdmcfnrcomevzvzardfrxxijhdezskkjqnawczrlvcydtgxbekhoihdnnojqtwqkybdmwmcktjavdntpkelyigpafn
konqblusehejnfhovgjonibdaprhmvtytzfegpseyygmcohuqgsfrvtnmtntyuxjolwmryunuozrjgouakxvwtnqyznqtcgpxhpzn
vqgmchgxqyqgladtudfpuvngmmmqslxkmfpbkumegwlseqbbeazffthicvdpldihmvrbkpltkcfffrymezjlugrfctndqeezgemdd
bjcjsquygrapdritfthekupyrgjuacrspxuathquovfujgiammxoscontersxrzsndrjfiazrsgggjzkyqvlmmoayslwitlthrlxf
etpmwonsikhwllsdhchgbsbvbxxvcfhsgzmtgkaeepdjckvuurreaypysfcqjbbdcpwndhqrwepgkshagvgxfuytjixpmnlhqafdn
fksyjjbvhelosknwxvhpfvvgmfyqietwqaiwkrfiedziudinitqvzumpbaiqoxtfrincokwdvwfgtbjsmtyahfejceeonthjwfnie
tukvfprdtlcbkkqgznvwtplwigjpfdkhcguuuwzeltywtvbcjsotlgtomhimycpnmjeufzeaxuagsyfkzhehznewuflldsdpaybrn
difbluvakvmbdwsevvsxfuvyrcradsetzjvzslfpmqjsytcswgdzmxekmgslwmdwhjhdmnkylkkvfvlrbzficgaegrekuxkbxvmvb
fneoynjhrzeggbpbdgmxfgdcpytpmaqozhijocvpiinevfpbuutmmvwmqqbkqehoisptcwbdliurhzactlcdxfdwzbhzrrfuiulxv
rnnubjptquhgwzcnegijrgdwcwweqrdzpjjqhuraiwqgunbmdymvnakgcbaelaefeyvmyvftapzrsxhynljvnyhgodvnbdoadadjv
hjqazrztasetevtkpuwjpevogicjeeefcjuzlriifdiwptgmkraeuaiqdyhmxnezswhusuprfukaimfqfzfjspcxhuyfopjbmhstd
jedoqupahdyeqmqmswnweiqdolvokydoilpzkkelrbguubykrzutyswcywjdqemxhhzcingsjqczhoyvfdiarjbjlyskgwejztowf
gekjrazbvvauhrczaeesaxaxflarcsllzmmlxbeuniougzldgtkdvhlththihlgdjfthjfxbrfwirudipzqnrgebeixqpvyciinal
xsjrtbrphgybzkjzwfgjpcwhhqktwzzlfewpvrjsbrxsgmbibvdhhuhwkkvylqbohxbdnlklljuququisemgvjuunhjivaijvbwvn
vqjmnymjvyejpgeplfxieleaopkxmnkzsyuxetrsavpsawoirfyzjdsiurlnlpoaaixdfctlotyrshvzwukyqcfqrxylhajzcugvl
ubnetkatpbhphnoayjoxlbhbrxvyxudozkdcwavkpxcdwqiwgidiobvvjdabxlwednfwogcsnkixbkipkqtybacnmnaenarjflxjs
yftkcgorvqakmkpllkvlgxkdvmmdklnxulxasfdvpvhdruckxhggumtszvqkfusrioiapvehmhvkyqhckmadcejawkpfwfxbtitii
kxpjmsjsljqtvzjirysomhfctpiinxcqfawuxtwztebebqghuahrrkwvqtwcgpkejjtikisbrbhzdcpbbfkcwqlymzyxkmjpafdqm
swfpgdeebrtmdnboonzabkthnwdslpibmqsttpqikinrttramqejmuyfxmbelklwafbxewnffggsrbsohpnxcbkdbxytuosfnemqa
lhdnhkgfnyuhdfaxpjjpshhbcgaehpwnxmieerolivijxavdzkspjmstrmurygmibhspotsoquqarqarmqkgngapyrtxbqglnfcye
glquxwmbekfopdtatdgumbbukuecmrgmrdhaszfmgpefoktdqyrxymlvzdyhwehhqnwmdizqlnjahchgssvvvvtuuvixtyfolnjei
twnwcgfsddswdryvljxqzmnfhpfozyxcduxgprfncmpzqlzlxeehzsqpqjyoavuiyiorfaxnpnypvnofuqzwtlckyezongiocgaif
kxvrminqmvyshztnurnhlndmwtceizmzbajhnxphsulnugknfkeegwlnukgyotxlbvbdlbfedknyxqtygwmjqohnzleqfvafutvou
keuufqyhwzugwmeyhklflldqcbeneuvqtupqzmixfafnovwacedgbkooqzldwzfqpbtfutggqvwymrpdilytdvmannrljgfqyvwhd
fxgcnslorvaovpobookhyyfdhogvktypyuvpkrzwlgdikomnengmawftvbrolxyzbuvzbqikjpkbzafhydlfqcyohtiqrzsqqsatc
jcccjchhlbekufuzlhuaxnkslrryukomcsbmbawbzhnnfekpbwsfdzmhtjyxnvdssruhivwwkbtydpffftftznkracmopaatcbqub
fzqkwzwmqqozhbkbdveqzwntclztodulyobknbonffxnidkdfuxdhumbpenwbasudnrkrlmonwokgldeazvyjejrulhdhbqsenbqz
utoyjxfidkxprtijyjtvjywdzijakceouigulfiullgbnuzskldphonhjqkytamqdmnshobidhkxxktiqcxjtoenklexxagvqrhvl
goohuovbprtsooucnrcnactwgicnsjvadhjbclataloaufjldxjmbglerdhcswrdvvdhotqrbhkronxhtjbuppynwsodaqiilsgeo
ikyyubdxbdgucbmkfokzgedqojqcyjbtpvseercjvjosmknakngmttlwtwcpaxcgyrmqekgaflwptocbeyuuujaomnjzmmtwxshti
mozuzrrjrjuveenakiksruufxchusrvhvtwmxjquvmjbabfmdyodrnrmgcoyhhoehiuthmpieqevmtynzxtaxopxqudmmtsgwusnk
whzilmxuwoxbsyfmarjzhnltzbnptlmgkoodsusebnspxwfgfvzsdjkhuhikpeinktwcafrdynhyztzuubonqzpojkxgseeugzedk
ztlrhmfklhweedcuouhxcudfqsxdetrkfjklggwpzmxofoukviqtsgszwailknenmzhxqpojymulrnxdtwnzrjyxgwhfpgllpoudf
pwshlzwebsnskgxagaaadnshcuirrupeyohaxbicoofbuknavoerffmcailtepqcgyuhikcprixlmjzmazykwlusbmfccvoyhwduu
mtbzjvqvwgtpcezumzmppjurybgswtxbojoyljbxawxftyhzhresxzdqjtmkwekcxbezjtacrzeacrqtpsodoidmzjdjaklskbevc
ynxjdfoudthjbwbpifatokkcpuiawepngbczgdpaztontrsuddinmcprnqhbbbowffcpwqzmlcjbscamynmswjlbhmkbpumugrvin
ltfeejmtregjdmjdnunonraavrfxyihoigzvmicmwadydwxdicoauuuuakdoyqpchaonrwxflmqgsbgzzsjkhlgfjqahhfnrtteuf
rzywkgqcqbehpeveuwazlezdecpjfowftvqwyoixcwizvrekewgrkvmcmekrxzqfsoozfuvebhepxhtszdtpnlocwoorckgzbfqbk
huomvkiibvybklvcrjtffxiuiazvmpjtvowtttdmchyyleibtgzirqomqfswtrhdlkfuhffhckivoawpgslnxgvdlfdycafrkdgih
kvdduycucvymflfakekltvtkwbmbyyvnlngspeqxkqpyrjjuckmkthbxipedchzdchgzpfdfiilidynainekjlpulewebuayrxbkq
mdcbjqgjvrwbquhrawxqtzgkuqwopdqjdayxdqwzjrxvwyrfafncntvnqybhzcbfrtfiqdkafxyqehserxizcqcgriitnytofqdld
jngrxdrpsckjhloimrlmyntfwppiqgnbewpgvwmrrwuvzfbdwpdapbcygfhgylvezlgkstiaxnhnnvudyhkpycivbbgqtzxlquqmc
czurbzatlhrurteeqsfbigmebmooaopyycoscenawcotuiedylbnciykprxttmakbhxfpykvrmpxetxdkornkjeskqwsypsiwqheg
zdcoyivuvzgaxfsbejpizkwisjsndfarbychhgbfdhgyotuafusjcpzrwpxexujkvooligzpfpvepymjdjzzmwrqeuuqyzamhflqh
vvocngtdlocloplxxuxbvlewsbhzqfftsmfcrfxqqcxmghuzmdgigwhgrahvgabsfsudcfodroromalnsbuciomayksrjmifkdixn
chpxpyttmhiqkxycwmbdjisigmqgrwnnhujshxyipvdptbdbsuarlgossnirardnjkubhaokljyxlyumzewxwjnveuhnrwopdxopx
mwbqxashemarvmtuvoianaqojlfgkizrrirpqoxlwzwyhwgzlpzvptwsuoscmbabgypivvvcszyenrzeqnsujhfmqektxqckjhahb
guhopfwftpmoaxdjbcscoliejwlhfuehjpzsxxssfpwtnqtfwpqfvopgboorjslgpklkqbcsduewvucsqrvathrouz"###;
        let output = 1027;
        let ret = Solution::partition_string(s);
        assert_eq!(output, ret);
        // Explanation:
        // The only valid partition is ("s","s","s","s","s","s").
    }
}
