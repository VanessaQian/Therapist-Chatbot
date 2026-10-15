#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>


using namespace std;

class Chat_bot {

    // Variables and vectors of expressions 
    
    string title;
    bool userHasTalked = false;

    vector<string> greeting = {"hello", "hi ", "hi!", "hi,"};
    vector<string> greetingReply = {"Hello! How are you feeling today?", "Hi! Do you want to chat?", 
        "Hey there! Anything troubling you recently?"};
    bool replyGreeting = false;

    // Vectors to identify user's mood
    vector<string> happy = {"great", "good", "amazing", "happy", "love", "grateful", "joy", "fun", "yay", 
        "yippie", "wow", "success", "fantasic", "enjoy", "excite", "!", ":)"};
    vector<string> sad = {"bad", "sad", "depressed", "unhappy", "lonely", "miserable", "heartbroken", 
        "down", "cry", "gloomy", "hopeless", "lost", "empty", "tears", ":(", "break up", "broke up"};
    vector<string> angry = {"angry", "mad", "furious", "rage", "irritate", "annoy", "frustrate", 
        "upset", "hate", "pissed", "resentful", "hostile", "offend", "aggressive", "bitter", ">:("};
    vector<string> anxious = {"anxious", "nervous", "worried", "stress", "panic", "uneasy", "scared", 
        "oh no", "problem", "overthink", "restless", "fail", "concern", "tense", "pain", "struggling", "struggle"};
    vector<string> funny = {"funny", "hilarious", "lol", "lmao", "haha", "hehe", "comedy", "laugh", 
        "joke", "humour", "goofy", "silly"};
    vector<string> harmfulWords = {"kill", "die", "suicide", "worthless", "useless", 
        "failure", "stupid", "misery", "suffer", "ashamed"};

    int isHappy = 0;
    int isSad = 0;
    int isAngry = 0;
    int isAnxious = 0;
    int isFunny = 0;
    bool isHarmful = false;

    // Topic indicator
    vector<string> school = {"class", "homework", "exam", "test", "teacher", "prof", "study", "assignment",  
        "lecture", "grade", "mark", "university", "college", "school", "quiz", "project", "report"};
    vector<string> relationship = {"friend", "crush", "love", "date", "relationship", "partner",  
        "boyfriend", "girlfriend", "married", "family", "bond", "connection", "bestie"};
    vector<string> duty = {"work", "job", "responsibility", "task", "chore", "errand", "duty",  
        "deadline", "schedule", "commitment", "goal", "career", "obligation", "assignment", "productivity"};

    bool isSchool = false;
    bool isRelationship = false;
    bool isDuty = false;

    // Vectors of responses
    vector<string> expressions = {"oh.", "umm ok", "interesting", "cool :D", "hmm", "sorry I don't quite understand", 
        "aha yes", "ehe", "im confused", "what?", "huh?", "hmm, want to tell me more?"};
    vector<string> expressionsHappy = {"That's great!", "I'm happy for you!!!", "Love to hear that!", 
        "Your smile really makes my day", "YIPPIE!", "YAYYYYYYYY", "LESGOOOOOOO", "This is amazing!!", "Nice!",
        "OMG exciting!!!"};
    vector<string> expressionsSad = {"Oh no", ":(((", "That sounds tough. Hope you feel better soon.", 
        "Take your time, and be kind to yourself", "Sometimes, things get hard, but you're not alone.",
        "You sound sad. Do you want to talk about it?"};
    vector<string> expressionsAngry = {"I get you. I would be mad too.", 
        "Venting helps me a lot. Do you wanna talk?",
        "Life sucks sometimes. Do you want to talk about it?", 
        "Anger is normal. I, too, want to punch things sometimes.",
        "You have every right to feel this way.", "You're so right. That is upsetting."};
    vector<string> expressionsAnxious = {
        "I know things are overwhelming right now, but I believe in you! You will get through it!",
        "One step at a time. You got this!", "I believe in you!",
        "You're stronger than you think. I'm sure about that.", 
        "Don't worry. I'm here for you!", "Oh no :("};
    vector<string> expressionsFunny = {"LMAOOOOOOOOO", "LMAO", "lol", "LOLOL", "HAHA", "TOP TIER COMEDY!",
        "HAHAHAHAHHAHAHAHHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA", "THAT WAS GOLD!", 
        "Ever considered becoming a comedian? You should."};
    vector<string> harmful = {"Hey, I know this may be tough, but you are amazing. I believe in you!",
        "I'm really sorry you're feeling this way. Remember, you're not alone in this, and there are people who care about you.",
        "I'm here for you. I will always be here for you.",
        "Please don't say that about yourself. I know you are so much better.",
        "It sounds like you're going through a really difficult time. Do you want to talk about it?", 
        "I'm listening. If things feel overwhelming, talking to a friend, family member, or professional can really help.",
        "You might be feeling this way now, but things can get better. You are stronger than you think.", 
        "You are valuable and loved. I hope I can support you, but consider reaching out to others for help as well.",
        "Even if you feel like you're alone in this, I will always be here for you. Don't give up!"
    };
    vector<string> schoolHappy = {"That's awesome! School wins are the best!", 
        "Sounds like you're having a great time! What happened?",
        "I love hearing good news! Tell me more!", 
        "That's so exciting! Hard work pays off!", 
        "Yeah!!! This is amazing! Good job", 
        "OMG I wish I could have been there with you. Sounds amazing!",
        "Wow! Am I in the presence of an academic weapon!?"
    };
    vector<string> schoolSad = {
        "Bad grades or tough days don't define you. You're still capable and smart.",
        "Oof. School can be tough. I hear you.",
        "It's okay to struggle sometimes. Learning isn't always easy.",
        "Don't be too sad. I can see that you are improving yourself!",
        "If you need a break, that's totally valid. Taking care of yourself matters too.",
        "You are more than just your grades. Don't be too hard on yourself"
    };
    vector<string> schoolAngry = {
        "Ugh, I get why that would make you mad. School can be so unfair sometimes!",
        "I'd be upset too if that happened. You deserve better.",
        "That sounds frustrating. Want to rant?",
        "Ugh, that sucks. I hate that too.",
        "I feel you. Let it out. Tell me more."
    };
    vector<string> schoolAnxious = {
        "School stress can feel overwhelming, but you'll get through this.", 
        "Sometimes, school feels overwhelming, but you are stronger than you think.",
        "It's okay to feel anxious about school. It means you care.",
        "Tests and assignments can be stressful, but you are more than capable!", 
        "Your hard work will pay off. Believe in yourself!"
    };
    vector<string> schoolFunny = {
        "Haha, that's hilarious! School is never boring, huh?", 
        "Wait, that actually happened? That's wild!",
        "Classic school chaos! Gotta love it!",
        "That's exactly the kind of story that makes school worth it!"
        "LOL! I can totally picture that happening!"
    };

    vector<string> relationshipHappy  = {
        "Sweet! Are you going to spend more time with them now?",
        "Sounds like the interaction went well!",
        "Sounds fun!",
        "Bet you made some great memories",
        "Ooooh, that sounds exciting! Tell me more!",
        "Tell me more! Tell me more! What happened."
    };
    vector<string> relationshipSad = {
        "Oh no. Relationships can be really tough sometimes.",
        "I sense that this relationship has made you sad. Do you want to talk about it?",
        "Humans are unpredictable. Don't be too hard on yourself.",
        "It's absolutely normal to feel hurt in this situation.",
        "Relationship problems can really hurt. Give yourself the time and space to heal."
    };
    vector<string> relationshipAngry = {
        "People can be so frustrating sometimes, but also realize that that is what makes them so fun!",
        "That's frustrating. Maybe try talking to them about it.",
        "You're right. You have every right to be mad.",
        "That's totally unfair. Want to vent some more?",
        "Some people just don't get it. Don't worry, I'm here to hear you out."
    };
    vector<string> relationshipAnxious = {
        "Confrontations can be nervewracking. Take a deep breath. You got this!",
        "You're not alone. Many others feel this way too.",
        "No need to rush. Relationships that crumble so easily aren't worth it.",
        "It's okay to feel anxious about this. Sometimes, relationships just take time to figure out."
        "Always remember that you are more important than anyone else. Help yourself before you help others."
    };
    vector<string> relationshipFunny = {
        "Lollll this is really what makes human connection worth it.",
        "LMAOOO that's ridculous! Tell me more!",
        "HAHAHA People sure are funny.",
        "Honestly, relationships should come with a warning label: 'Expect the unexpected!'"
        "Everyday life can have such funny moments."
    };

    vector<string> dutyHappy = {
        "You did great! Give yourself a pat on the back",
        "Love to hear that! What was the highlight for you?",
        "Nice! Getting things done is so satisfying.",
        "I knew you would succeed! Congrats!",
        "Bet that feels like a weight off your shoulders!",
        "That's fantastic! You should be proud of yourself!"
    };
    vector<string> dutySad = {
        "I'm really sorry to hear that. It's tough when duties start piling up.", 
        "I know it's hard, but you're strong. Don't let it break you down.",
        "It sucks when everything is on your shoulders. But don't forget, there are people there to support you.",
        "Sometimes, it is just luck. It sucks, but maybe you'll have better luck next time! Don't give up!"
        "Hey, don't be too sad. Remember to look for the positives even in the worst moments. Want to talk?"
    };
    vector<string> dutyAngry = {
        "This sounds so frustrating! Sometimes it feels like you're being treated like a robot.",
        "Ugh, that's so unreasonable. I would be upset too.",
        "Since when did people start having so much to do. That really sucks.",
        "That's crazy. No one should expect you to do that much. Want to tell me more?",
        "It's so annoying when it feels like you're carrying all the weight. I get why you're upset."
    };
    vector<string> dutyAnxious = {
        "Oh my that sounds overwhelming! Please, you deserve a break.",
        "Anxiety can make everything feel bigger than it is. Let's take this one step at a time.",
        "It may look like a lot right now, but break it down and, slowly, it may not be as bad.",
        "Take a deep breath. One step at a time. It will be over soon!",
        "Don't worry. I have trust in your abilities!"
    };
    vector<string> dutyFunny = {
        "Lmaooo so unexpected!",
        "I thought responsibilities were pure boring, but you've proved me wrong!",
        "You have got to tell me more stories about your duties sometime.",
        "Haha, that's so funny! It reminds me of the comedy dramas about work!"
    };
    
public:
    Chat_bot (string name) {
        title = name;
    }

    // returns the name of this chatbot
	string name() const {
        return title;
    }

	// gives a string to this chatbot
    // determines mood (happy, sad, angry, anxious, funny, or harmful) and topic (school, relationship, work)
	void give_to(const string &s) {
        userHasTalked = true;
        // convert all to lowercase
        string s1;
        for (char c:s) {
            s1 += (char)tolower(c);
        }
        // Defaults
        isHappy = 0;
        isSad = 0;
        isAngry = 0;
        isAnxious = 0;
        isFunny = 0;
        isHarmful = false;

        isSchool = false;
        isRelationship = false;
        isDuty = false;

        replyGreeting = false;
        for (string phrase: greeting){
            if (s1.find(phrase) != string::npos) {
                replyGreeting = true;
            };
        }
        
        // Read user emotion
        for (string phrase: happy){
            if (s1.find(phrase) != string::npos) {
                isHappy++;
            };
        }
        for (string phrase: sad){
            if (s1.find(phrase) != string::npos) {
                isSad++;
            };
        }
        for (string phrase: angry){
            if (s1.find(phrase) != string::npos) {
                isAngry++;
            };
        }
        for (string phrase: anxious){
            if (s1.find(phrase) != string::npos) {
                isAnxious++;
            };
        }
        for (string phrase: funny){
            if (s1.find(phrase) != string::npos) {
                isFunny++;
            };
        }
        for (string phrase: harmfulWords){
            if (s1.find(phrase) != string::npos) {
                isHarmful = true;
            };
        }

        // Read user's topic
        for (string phrase: school){
            if (s1.find(phrase) != string::npos) {
                isSchool = true;
            };
        }
        for (string phrase: relationship){
            if (s1.find(phrase) != string::npos) {
                isRelationship = true;
            };
        }
        for (string phrase: duty){
            if (s1.find(phrase) != string::npos) {
                isDuty = true;
            };
        }
    }

	// gets a string from this chatbot
    // outputs string from pre-existing vectors of responses
    // choose a response based on mood and topic
	string get_from() {
        if (!userHasTalked) {
            return "Hi! How are you feeling today?";
        }

        srand(time(nullptr));
        if (replyGreeting) {
            return greetingReply.at(rand() % greetingReply.size());
        }

        int emotion = -1;
        if (max({isHappy, isSad, isAngry, isAnxious, isFunny}) != 0)
            emotion = max({isHappy, isSad, isAngry, isAnxious, isFunny});
        if (isHarmful) {
            return harmful.at(rand() % harmful.size());
        }
        if (isSchool) {
            if (emotion == isHappy) {
                return schoolHappy.at(rand() % schoolHappy.size());
            }
            if (emotion == isSad) {
                return schoolSad.at(rand() % schoolSad.size());
            }
            if (emotion == isAngry) {
                return schoolAngry.at(rand() % schoolAngry.size());
            }
            if (emotion == isAnxious) {
                return schoolAnxious.at(rand() % schoolAnxious.size());
            }
            if (emotion == isFunny) {
                return schoolFunny.at(rand() % schoolFunny.size());
            }
        }
        if (isRelationship) {
            if (emotion == isHappy) {
                return relationshipHappy.at(rand() % relationshipHappy.size());
            }
            if (emotion == isSad) {
                return relationshipSad.at(rand() % relationshipSad.size());
            }
            if (emotion == isAngry) {
                return relationshipAngry.at(rand() % relationshipAngry.size());
            }
            if (emotion == isAnxious) {
                return relationshipAnxious.at(rand() % relationshipAnxious.size());
            }
            if (emotion == isFunny) {
                return relationshipFunny.at(rand() % relationshipFunny.size());
            }
        }
        if (isDuty) {
            if (emotion == isHappy) {
                return dutyHappy.at(rand() % dutyHappy.size());
            }
            if (emotion == isSad) {
                return dutySad.at(rand() % dutySad.size());
            }
            if (emotion == isAngry) {
                return dutyAngry.at(rand() % dutyAngry.size());
            }
            if (emotion == isAnxious) {
                return dutyAnxious.at(rand() % dutyAnxious.size());
            }
            if (emotion == isFunny) {
                return dutyFunny.at(rand() % dutyFunny.size());
            }
        }
        if (emotion == isHappy) {
            return expressionsHappy.at(rand() % expressionsHappy.size());
        }
        if (emotion == isSad) {
            return expressionsSad.at(rand() % expressionsSad.size());
        }
        if (emotion == isAngry) {
            return expressionsAngry.at(rand() % expressionsAngry.size());
        }
        if (emotion == isAnxious) {
            return expressionsAnxious.at(rand() % expressionsAnxious.size());
        }
        if (emotion == isFunny) {
            return expressionsFunny.at(rand() % expressionsFunny.size());
        }
        return expressions.at(rand() % expressions.size());
    }

	// destructor
	~Chat_bot() {}

};

// User conversation with bot. The bot goes first.
// Ends when the user types the string "!done".
void converse_with_user(Chat_bot* bot) {
    cout << "Conversation with "
         << bot->name() << " (type !done to quit)\n\n";

    string user_reply;
    int turn = 1;
    while (user_reply != "!done"){
        string bot_reply = bot->get_from();
        cout << bot->name() << " " << turn << "> " << bot_reply << "\n";

        cout << "User " << turn << "> ";
        getline(cin, user_reply);
        cout << endl;

        bot->give_to(user_reply);
        turn++;
    } 

    cout << "User conversation with " << bot->name() << " ended\n";
}

int main()
{
    Chat_bot therapist("Bob");
    converse_with_user(&therapist);
}
