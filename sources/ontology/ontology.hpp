#pragma once

#include "kernel/framework/module/module.hpp"
#include "kernel/utility/macroses/holy_trinity.hpp"

namespace onto
{
class Ontology : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(Ontology);

    // void initialize() noexcept override;
    // void terminate() noexcept override;
    // bool loopBody() noexcept override;

    // void commandSetup() const noexcept override;
private:
    Ontology() noexcept;
};
} // namespace onto
