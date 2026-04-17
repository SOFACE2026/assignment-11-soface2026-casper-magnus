#pragma once
#include <algorithm>
#include <vector>
#include <tuple>
#include <iterator>
#include <optional>

/**
 * @brief Container used to store assoicate keys with values.
 * values can later be retrived using the corresponding key.
 * 
 * @tparam K type of the keys stored in the dictionary.
 * @tparam V type of the values assoicated with each key.
 */
template <class K, class V>
class Dict
{
private:
    // Vi gemmer vores data som en vektor af "par" (std::pair).
    // Hvert par indeholder en nøgle (K) og en tilhørende værdi (V).
    std::vector<std::pair<K, V>> data;

public:
    /**
     * @brief Associates the key with the specified value.
     * If the key is already in the dictionary its value is overwritten.
     * 
     * @param key key associated with the provided key.
     * @param val value assoicated with the provided key.
     */
    void set(K key, V val)
    {
        // Vi kører igennem alle par i vores data-vektor (som referencer for at kunne ændre dem).
        for (auto& pair : data) {
            // Hvis vi finder et par, hvor nøglen (pair.first) allerede findes -
            if (pair.first == key) {
                // - så overskriver vi bare værdien (pair.second) med den nye.
                pair.second = val;
                return; // Afslut funktionen herindefra
            }
        }
        // Hvis vi har kigget hele listen igennem uden at finde nøglen,
        // tilføjer vi et helt nyt nøgle-værdi par i bunden af vektoren.
        data.push_back({key, val});
    }

    /**
     * @brief Determines if the key is defined in the dictionary.
     * 
     * @param key key for which to look for.
     * @return true if the key is defined in the dictionary.
     * @return false otherwise.
     */
    bool has(K key) const
    {
     
        return std::any_of(data.begin(), data.end(), [&key](const auto& pair) {
            return pair.first == key; // Sammenligner nøglen med eksisterende nøgler
        });
    }

    /**
     * @brief Returns the number of items in the dictionary.
     * 
     * @return the number of items in the dictionary.
     */
    size_t len() const
    {
        // Returnerer blot hvor mange par der aktuelt er gemt i vores vektor.
        return data.size();
    }

    /**
     * @brief Get the value associated with the specified key.
     * If no value is found std::nullopt is returned.
     * 
     * @param key key for which to locate value.
     * @return value associated with key.
     */
    std::optional<V> get(K key) const
    {
        // Kører igennem alle par i vores ordbog.
        for (const auto& pair : data) {
            // Hvis vi finder den efterspurgte nøgle:
            if (pair.first == key) {
                return pair.second; // Returner dens tilhørende værdi.
            }
        }
        // Hvis vi når hertil, fandtes nøglen ikke. Så returnerer vi std::nullopt.
        return std::nullopt;
    }

    /**
     * @brief Delete the specified key and its associated value
     * from the dictionary.
     * If the key is not present in the dictionary, nothing happens.
     * 
     * @param key A key currently present in the dictionary
     * which will be deleted.
     */
    void del(K key)
    {
        
        auto it = std::remove_if(data.begin(), data.end(), [&key](const auto& pair) {
            return pair.first == key;
        });
        
        // Hvis der faktisk blev fundet og flyttet noget...
        if (it != data.end()) {
            // ...så sletter vi dem permanent fra vektoren.
            data.erase(it, data.end());
        }
    }

    /**
     * @brief List all keys of the dictionary.
     * 
     * @return vector of keys.
     */
    std::vector<K> keys() const
    {
        std::vector<K> result;
        // Vi allokerer plads i forvejen for effektivitetens skyld, da vi kender antallet.
        result.reserve(data.size());
        
        // Gennemløb alle par i ordbogen
        for (const auto& pair : data) {
            // Udtræk kun nøglen (pair.first) og put den i resultat-vektoren
            result.push_back(pair.first);
        }
        return result; // Returnér vektoren fyldt med nøgler
    }

    /**
     * @brief List all values of the dictionary.
     * 
     * @return vector of values.
     */
    std::vector<V> values() const
    {
        std::vector<V> result;
        // Vi allokerer plads i forvejen.
        result.reserve(data.size());
        
        for (const auto& pair : data) {
            // Udtræk kun værdien (pair.second) og put den i resultat-vektoren
            result.push_back(pair.second);
        }
        return result; // Returnér vektoren fyldt med værdier
    }
};
