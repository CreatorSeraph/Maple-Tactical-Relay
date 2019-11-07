//제작자 CreatorSeraph(git hub)
//메이플 닉 TRSeraph
//배포 가능, 수정가능
//대신에 퍼가실때 제 이름만 남겨주세용

#include <iostream>
#include <queue>
#include <string>
#include <array>
#include <list>

enum 직업
{
    궁수, 도적, 해적, 전사, 법사, 제논
};

int main()
{
    constexpr bool dailyCheck = false;
    using namespace std;
    auto lastOutLocale = wcout.imbue(locale("korean"));
    auto lastInLocale = wcin.imbue(locale("korean"));

    constexpr size_t 직업_개수 = 6;
    array <list<wstring>, 직업_개수 > 이름_저장소;
    array<wstring, 직업_개수> 직업_문자열 = { L"궁수" ,L"도적", L"해적", L"전사", L"법사", L"제논" };
    wstring 입력저장용;
    int 캐릭터개수 = 0;

    wcout << L"앞으로 나오는 직업군의 200레벨 이상 캐릭터 이름을 입력해주세요 (없으면 0 입력)" << endl;

    for (int i = 0; i < 직업_개수; ++i)
    {
        while (true)
        {
            wcout << 직업_문자열[i] << L": ";
            wcin >> 입력저장용;

            if (입력저장용 == L"0")
                break;
            이름_저장소[i].push_back(std::move(입력저장용));
            ++캐릭터개수;
        }
    }

    int 총점 = 0;

    for(int 날짜 = 7; 날짜 <= 20; ++날짜)
    {
        if constexpr (dailyCheck)
        {
            wcout << endl << endl;
            wcout << L"원하는 날짜를 ""숫자로"" 입력해 주세요. (7~20)" << endl;
            wcout << L"종료를 원하시면 0을 입력해 주세요. : ";

            wcin >> 입력저장용;

            try
            {
                날짜 = stoi(입력저장용);
            }
            catch (std::invalid_argument e)
            {
                wcout << L"숫자로 입력해 주세요 ㅠㅠ" << endl;
                continue;
            }

            if (날짜 == 0)
                break;
            if (날짜 < 7 || 날짜 > 20)
            {
                wcout << L"택티컬 릴레이 기간이 아닙니다" << endl;
                continue;
            }
        }

        auto 복사된_저장소 = 이름_저장소;
        int 현재_캐릭터_개수 = 캐릭터개수;
        auto pop = [&복사된_저장소, &현재_캐릭터_개수](int job)
        {
            wstring result = 복사된_저장소[job].front();
            복사된_저장소[job].pop_front();
            --현재_캐릭터_개수;
            return result;
        };

        array<wstring, 9> 미션들 = {
            L"레범몬300",
            L"콤보100\t",
            L"일일보스",
            L"스타포스300",
            L"몬파1\t",
            L"룬1\t",
            L"엘몹3\t",
            L"멀티킬100",
            L"아케인300",
        };

        int 점수 = 450;
        array<wstring, 9> 필요_캐릭터;
        int i;
        //직업조건, 레벨조건 만족하는 캐릭터
        for (i = 8; i >= 0 && 현재_캐릭터_개수 > 1; --i)
        {
            auto 필요_직업 = (날짜 + i) % 5;

            if (!복사된_저장소[필요_직업].empty())
            {
                필요_캐릭터[i] = pop(필요_직업);
            }
            else if ((필요_직업 == 도적 || 필요_직업 == 해적) && !복사된_저장소[제논].empty())
                필요_캐릭터[i] = pop(제논);
        }
        
        list<wstring> 남은_캐릭터;
        for (auto& iter : 복사된_저장소)
        {
            남은_캐릭터.splice(남은_캐릭터.begin(), iter);
        }
        
        //레벨 조건 만족하는 캐릭터
        for (i = 8; i >= 0 && !남은_캐릭터.empty(); --i)
        {
            if (필요_캐릭터[i].empty())
            {
                필요_캐릭터[i] = 남은_캐릭터.front();
                남은_캐릭터.pop_front();
                점수 += 20;
            }
            else
                점수 += 30;
        }

        while (i >= 0)
        {
            if(필요_캐릭터[i].empty())
            {
                필요_캐릭터[i] = 직업_문자열[(날짜 + i) % 5];
                점수 += 10;
            }
            i--;
        }

        wcout << L"11월" << 날짜 << L"일 (" << 날짜 - 6 << L"일차)" << endl;

        for (i = 0; i < 9; ++i)
        {
            wcout << 미션들[i] << L"\t:" << 필요_캐릭터[i] << endl;
        }

        wcout << L"점수 : " << 점수;

        if constexpr (dailyCheck)
        {
            날짜 = 7;
            cout << endl;
        }
        else
        {
            총점 += 점수;
            wcout << L"\t총점 : " << 총점 << endl;
        }
    }
}
