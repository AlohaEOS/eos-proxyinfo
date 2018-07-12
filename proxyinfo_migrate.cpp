#include <eosiolib/eosio.hpp>

/**
 * This is a hack to assist with migrating table data to a new schema. The sequence goes like this:
 *     1) update proxyinfo and proxyinfo_migrate contracts with proper structs for migration
 *     2) set proxyinfo_migrate contract
 *     3) push action migratetotmp (moving ram usage from proxies to regproxyinfo account)
 *     4) verify data in proxiestmp table
 *     5) push action eraseorig
 *     6) set proxyinfo contract
 *     7) push action migratetmp
 *     8) verify data in proxies table
 *     9) push action erasetmp
 * 
 */
class proxyinfo_contract : public eosio::contract {
    public:
        proxyinfo_contract(account_name self)
        :eosio::contract(self),
        proxies(_self, _self),
        proxiestmp(_self, _self)
        {}

        void migratetotmp() {
            require_auth(_self);
            for (const auto & row : proxies) {
                eosio::print("Migrating owner=", row.owner, ", name=", row.name, ", website=", row.website, "\n");
                proxiestmp.emplace(_self, [&](auto & i) {
                    i.owner = row.owner;
                    i.name = row.name;
                    i.website = row.website;
                });
            }
        }

        void erasetmp() {
            require_auth(_self);
            for(auto itr = proxiestmp.begin(); itr != proxiestmp.end();) {
                itr = proxiestmp.erase(itr);
            }
        }

        void eraseorig() {
            require_auth(_self);
            for(auto itr = proxies.begin(); itr != proxies.end();) {
                itr = proxies.erase(itr);
            }
        }

    private:
        // @abi table proxies i64
        struct proxy {
            account_name owner;
            std::string name;
            std::string website;

            auto primary_key()const { return owner; }
            EOSLIB_SERIALIZE(proxy, (owner)(name)(website))
        };

        typedef eosio::multi_index<N(proxies), proxy> proxy_table;
        proxy_table proxies;

        // @abi table proxiestmp i64
        struct proxytmp {
            account_name owner;
            std::string name;
            std::string website;

            auto primary_key()const { return owner; }
            EOSLIB_SERIALIZE(proxytmp, (owner)(name)(website))
        };

        typedef eosio::multi_index<N(proxiestmp), proxytmp> proxytmp_table;
        proxytmp_table proxiestmp;
};

EOSIO_ABI(proxyinfo_contract, (migratetotmp)(erasetmp)(eraseorig))
