 int matchTokenType (const char * input_str, tokenType type) {
    // given input string and type, return the length of the match
    int match_length = 0;
    switch (type) {
        case intKwd: // something
            break;
        case floatKwd:
    }

    // if doesn't match, return 0
    return match_length;
}

class Token * matchToken(const char * input_str) {
    // for all types, find the matched one that gives the maximum length

    class Token *token_matched = new Token;
    int max_length = -1;
    tokenType type_matched = last;

    for (int index = 0; index != last ; index++)
        tokenType type = static_cast<tokenType>(index);
        int length = matchTokenType(input_str, type);
        if (length > max_length) {
            max_length = length;
            type_matched = type;
        } else if (length == max_length) {
            cout << "conflict happens between " << type << "and "  << type_matched << endl;
            return NULL;
        }
    }
    return matched;
}
