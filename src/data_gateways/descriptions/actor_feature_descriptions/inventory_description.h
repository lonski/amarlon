#ifndef INVENTORY_DESCRIPTION
#define INVENTORY_DESCRIPTION

#include <description.h>
#include <actor_type.h>
#include <vector>

namespace amarlon {

struct PickableDescription;
struct AiDescription;
struct OpenableDescription;
struct WearerDescription;
struct DestroyableDescription;

struct InventoryDescription : Description
{
  InventoryDescription() : maxSize(0) {}

  struct Content
  {
    ActorType actorType;
    //TODO: repalce Content with ActorDescription struct
    std::shared_ptr<InventoryDescription> container;
    std::shared_ptr<PickableDescription> pickable;
    std::shared_ptr<Description> character;
    std::shared_ptr<AiDescription> ai;
    std::shared_ptr<OpenableDescription> openable;
    std::shared_ptr<WearerDescription> wearer;
    std::shared_ptr<DestroyableDescription> destroyable;

    Content()
      : actorType(ActorType::Null)
    {
    }
  };

  size_t maxSize;
  std::vector<Content> content;
};

typedef std::shared_ptr<InventoryDescription> InventoryDescriptionPtr;

}

#endif // INVENTORY_DESCRIPTION

