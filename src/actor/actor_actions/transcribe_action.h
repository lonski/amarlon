#ifndef TRANSCRIBE_ACTION_H
#define TRANSCRIBE_ACTION_H

#include <memory>
#include <vector>
#include <actor_action.h>

namespace amarlon {

class Scroll;
typedef std::shared_ptr<Scroll> ScrollPtr;

class TranscribeAction : public ActorAction
{
public:
    TranscribeAction(ScrollPtr scroll);
    virtual ~TranscribeAction();

    virtual ActorActionResult perform(ActorPtr performer);
    virtual ActorActionUPtr clone();

private:
    ActorPtr _performer;
    ScrollPtr _scroll;

    void removeTranscribedScrollFromInventory();

};

typedef std::shared_ptr<TranscribeAction> TranscribeActionPtr;
typedef std::unique_ptr<TranscribeAction> TranscribeActionUPtr;

}

#endif // TRANSCRIBE_ACTION_H
