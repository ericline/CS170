/*!*****************************************************************************
\file    spellcheck.cpp
\author  Eric Lin
\par     DP email: eric.lin@digipen.edu
\par     Course: CS170
\par     Programming Assignment #7
\date    04-22-2022

\brief
  This program contains functions to manipulate given text files and implements a
  spell checker.
  
  - GetInfo
      Returns some information about a dictionary.

  - WordsStartingWith        
      Counts the number of words that start with a given letter.

  - WordLengths
      Counts the number of words that have length 1 to a given count.

  - SpellCheck
      Spellchecker that determines whether or not a given word is in the
      dictionary.

  - AcronymToWord
      Finds words in the dictionary that are composed of the same letters
      in the same order.
      
  - UpperCase
      Converts a string to uppercase.

  - Tokenize
      Splits a string into individual words.

  - WordWrap
      Breaks a string into lines less than equal to a given line length.
      
*******************************************************************************/

#include <fstream>        // ifstream
#include <string>         // string
#include <vector>         // vector
#include "FileStrings.h"  // SpellChecker, StringUtils, DictionaryInfo

namespace CS170
{
/*!*****************************************************************************
\brief
    Constructor for class SpellChecker.

\return 
    N/A
*******************************************************************************/
    SpellChecker::SpellChecker(const std::string &dictionary)
    {
        dictionary_ = dictionary;
    }

/*!*****************************************************************************
\brief
    Return some information about the dictionary using the reference parameter. 

\param
    info - address of dictionary info containing longest, shortest, and count.

\return 
    If the file can't be opened, returns scrFILE_ERR_OPEN, 
    otherwise returns scrFILE_OK.
*******************************************************************************/
    SpellChecker::SCResult SpellChecker::GetInfo(DictionaryInfo &info) const
    {
        std::fstream dictionary;

        dictionary.open(dictionary_.c_str());

        if(!dictionary)
        {
            return scrFILE_ERR_OPEN;
        }
        else
        {
            while(!dictionary.eof())
            {
                std::string word;
                dictionary >> word;

                if(info.longest < word.length())
                {
                    info.longest = word.length();
                }

                if(info.shortest > word.length())
                {
                    info.shortest = word.length();
                }

                info.count++;
            }
        }

        dictionary.close();
        return scrFILE_OK;
    }

/*!*****************************************************************************
\brief
    Looks up a given word in the dictionary. 

\param
    word - given that is being looked for.

\return 
    If the file can't be opened, returns scrFILE_ERR_OPEN, 
    otherwise returns scrFILE_OK.
*******************************************************************************/
    SpellChecker::SCResult SpellChecker::SpellCheck(const std::string& word) const
    {
        std::fstream dictionary;
        std::string copy_word = word;

        dictionary.open(dictionary_.c_str());
        if(!dictionary)
        {
            return scrFILE_ERR_OPEN;
        }
        else
        {
            while(!dictionary.eof())
            {
                std::string dict_word;
                dictionary >> dict_word;

                std::string upperDictWord = StringUtils::UpperCase(dict_word);
                std::string upperWord = StringUtils::UpperCase(copy_word);

                if(upperDictWord == upperWord)
                {
                    dictionary.close();
                    return scrWORD_OK;
                }
            }
        }
        dictionary.close();
        return scrWORD_BAD;
    }

/*!*****************************************************************************
\brief
    Counts the number of words that have length 1 to count and store them in the 
    vector lengths at the appropriate index.

\param
    lengths - vector that words are being stored into.
    count - maximum word length.

\return 
    If the file can't be opened, returns scrFILE_ERR_OPEN, 
    otherwise returns scrFILE_OK.
*******************************************************************************/
    SpellChecker::SCResult SpellChecker::WordLengths(std::vector<size_t>& lengths, size_t count) const
    {
        std::fstream dictionary;

        dictionary.open(dictionary_.c_str());
        if(!dictionary)
        {
            return scrFILE_ERR_OPEN;
        }
        else
        {
            while(!dictionary.eof())
            {
                std::string word;
                dictionary >> word;

                if(word.length() <= count)
                {
                    lengths[word.length() - 1]++;
                }
            }
        }
        dictionary.close();
        return scrFILE_OK;

        
    }
    
/*!*****************************************************************************
\brief
    Counts the number of words that start with a given letter.

\param
    letter - letter that is being looked for.
    count - total number of words.

\return 
    If the file can't be opened, returns scrFILE_ERR_OPEN, 
    otherwise returns scrFILE_OK.
*******************************************************************************/
    SpellChecker::SCResult SpellChecker::WordsStartingWith(char letter, int& count) const
    {
        std::fstream dictionary;

        dictionary.open(dictionary_.c_str());

        if(!dictionary)
        {
            return scrFILE_ERR_OPEN;
        }
        else
        {
            while(!dictionary.eof())
            {
                std::string word;
                dictionary >> word;
                char UpperLetter = letter;

                if(letter >= 'a' && letter <= 'z')
                {
                    UpperLetter = static_cast<char>(letter - 32);
                }

                std::string UpperWord = StringUtils::UpperCase(word);
                
                if(UpperWord[0] == UpperLetter)
                {
                    count++;
                }
            }
        }

        dictionary.close();
        return scrFILE_OK;

    }

/*!*****************************************************************************
\brief
    Given a string, find words in the dictionary that are composed of the 
    letters in the same order.

\param
    acronym - given acronym.
    words - vector that acronyms are being stored into.
    maxlen - max length of words that are being searched.

\return 
    If the file can't be opened, returns scrFILE_ERR_OPEN, 
    otherwise returns scrFILE_OK.
*******************************************************************************/
    SpellChecker::SCResult SpellChecker::AcronymToWord(const std::string& acronym, std::vector<std::string>& words, size_t maxlen) const
    {
        std::fstream dictionary;
        std::string copy_acronym = acronym;

        dictionary.open(dictionary_.c_str());

        if(!dictionary)
        {
            return scrFILE_ERR_OPEN;
        }
        else
        {
            std::string upper_acronym = StringUtils::UpperCase(copy_acronym);

            while(!dictionary.eof())
            {
                std::string word;
                bool hasAcronym = true;
                size_t start_index = 0;
                dictionary >> word;

                std::string upper_word = StringUtils::UpperCase(word);

                if(word.length() <= maxlen)
                {
                    for(size_t i = 0; i < upper_acronym.length(); i++)
                    {
                        if(hasAcronym)
                        {
                            for(size_t j = start_index; j < upper_word.length(); j++)
                            {
                                if(upper_acronym[i] != upper_word[j])
                                {
                                    hasAcronym = false;
                                }
                                else if(upper_acronym[i] == upper_word[j])
                                {
                                    hasAcronym = true;
                                    start_index = j;
                                    break;
                                }
                            }
                        }
                    }

                    if(hasAcronym)
                    {
                        words.push_back(word);
                    }
                }
            }
        }

        dictionary.close();
        return scrFILE_OK;
    }

/*!*****************************************************************************
\brief
    Converts a string to uppercase.

\param
    string - given string for conversion.

\return 
    The uppercase string.
*******************************************************************************/
    std::string& StringUtils::UpperCase(std::string& string)
    {
        std::string::iterator it;
        for (it = string.begin(); it != string.end(); ++it)
            if (*it >= 'a' && *it <= 'z')
                *it = static_cast<char>(*it - SPACE);

    
        return string;
    }
    
 /*!*****************************************************************************
\brief
    Splits a string into individual words.

\param
    word - the string being broken up.

\return 
    The broken up string.
*******************************************************************************/
    std::vector<std::string> StringUtils::Tokenize(const std::string& words)
    {
        std::vector<std::string> token_words;
        std::string word = "";

        for(size_t i = 0; i < words.length(); i++)
        {
            if(words[i] != ' ')
            {
                word += words[i];
            }
            else
            {
                token_words.push_back(word);
                word = "";
            }
        }

        return token_words;
    }

 /*!*****************************************************************************
\brief
    Break a string into lines less than or equal to a given line length.

\param
    words - the given string.
    line_length - the maximum line length that the string is being broken into

\return 
    The broken up string.
*******************************************************************************/
    std::vector<std::string> StringUtils::WordWrap(const std::string& words, size_t line_length)
    {
        std::vector<std::string> lines;
        std::string word = "";
        std::string line = "";
        bool line_full = false;

        for(size_t i = 0; i < words.length(); i++)
        {
            for(size_t j = i; j < words.length(); j++)
            {
                if(words[j] != ' ')
                {
                    word += words[j];
                }
                else if(word.length() + line.length() > line_length)
                {
                    line_full = true;
                    word += ' ';
                    break;
                }
                else
                {
                    line += word;

                    if(line.length() < line_length)
                    {
                        line += ' ';
                    }

                    word = "";

                    if(line.length() == line_length)
                    {
                        line_full = true;
                        break;
                    }
                }
            }

            if(line_full)
            {
                lines.push_back(line);
                line = "";
            }
        }

        return lines;
    }


}
