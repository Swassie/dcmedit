#pragma once
#include "common/Progress_token.h"

class Progress_token_stub : public Progress_token
{
    void set_max_progress(int) override {}
    void increment_progress() override {}
    bool cancelled() const override {return false;}
};
