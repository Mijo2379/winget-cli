// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#include "pch.h"
#include "ConfigurationSet.h"
#include "ConfigurationSet.g.cpp"
#include "ConfigurationSetParser.h"

namespace winrt::Microsoft::Management::Configuration::implementation
{
    ConfigurationSet::ConfigurationSet()
    {
        GUID instanceIdentifier;
        THROW_IF_FAILED(CoCreateGuid(&instanceIdentifier));
        m_instanceIdentifier = instanceIdentifier;
        m_schemaVersion = ConfigurationSetParser::LatestVersion();
    }

    ConfigurationSet::ConfigurationSet(const guid& instanceIdentifier) :
        m_instanceIdentifier(instanceIdentifier)
    {
    }

    void ConfigurationSet::Units(std::vector<Configuration::ConfigurationUnit>&& units)
    {
        m_units = winrt::single_threaded_vector<Configuration::ConfigurationUnit>(std::move(units));
    }

    void ConfigurationSet::Parameters(std::vector<Configuration::ConfigurationParameter>&& value)
    {
        m_parameters = winrt::single_threaded_vector<Configuration::ConfigurationParameter>(std::move(value));
    }

    bool ConfigurationSet::IsFromHistory() const
    {
        return false;
    }

    hstring ConfigurationSet::Name()
    {
        return m_name;
    }

    void ConfigurationSet::Name(const hstring& value)
    {
        m_name = value;
    }

    hstring ConfigurationSet::Origin()
    {
        return m_origin;
    }

    void ConfigurationSet::Origin(const hstring& value)
    {
        m_origin = value;
    }

    hstring ConfigurationSet::Path()
    {
        return m_path;
    }

    void ConfigurationSet::Path(const hstring& value)
    {
        m_path = value;
    }

    guid ConfigurationSet::InstanceIdentifier() const
    {
        return m_instanceIdentifier;
    }

    ConfigurationSetState ConfigurationSet::State()
    {
        return ConfigurationSetState::Unknown;
    }

    clock::time_point ConfigurationSet::FirstApply()
    {
        return m_firstApply;
    }

    clock::time_point ConfigurationSet::ApplyBegun()
    {
        return clock::time_point{};
    }

    clock::time_point ConfigurationSet::ApplyEnded()
    {
        return clock::time_point{};
    }

    Windows::Foundation::Collections::IVector<Configuration::ConfigurationUnit> ConfigurationSet::Units()
    {
        return m_units;
    }

    void ConfigurationSet::Units(const Windows::Foundation::Collections::IVector<ConfigurationUnit>& value)
    {
        THROW_HR_IF(E_POINTER, !value);
        m_units = value;
    }

    hstring ConfigurationSet::SchemaVersion()
    {
        return m_schemaVersion;
    }

    void ConfigurationSet::SchemaVersion(const hstring& value)
    {
        THROW_HR_IF(E_INVALIDARG, !ConfigurationSetParser::IsRecognizedSchemaVersion(value));
        m_schemaUri = ConfigurationSetParser::GetSchemaUriForVersion(value);
        m_schemaVersion = value;
    }

    event_token ConfigurationSet::ConfigurationSetChange(const Windows::Foundation::TypedEventHandler<WinRT_Self, ConfigurationSetChangeData>& handler)
    {
        return m_configurationSetChange.add(handler);
    }

    void ConfigurationSet::ConfigurationSetChange(const event_token& token) noexcept
    {
        m_configurationSetChange.remove(token);
    }

    void ConfigurationSet::Serialize(const Windows::Storage::Streams::IOutputStream& stream)
    {
        UNREFERENCED_PARAMETER(stream);
        THROW_HR(E_NOTIMPL);
    }

    void ConfigurationSet::Remove()
    {
        THROW_HR(E_NOTIMPL);
    }

    Windows::Foundation::Collections::ValueSet ConfigurationSet::Metadata()
    {
        return m_metadata;
    }

    void ConfigurationSet::Metadata(const Windows::Foundation::Collections::ValueSet& value)
    {
        THROW_HR_IF(E_POINTER, !value);
        m_metadata = value;
    }

    Windows::Foundation::Collections::IVector<ConfigurationParameter> ConfigurationSet::Parameters()
    {
        return m_parameters;
    }

    void ConfigurationSet::Parameters(const Windows::Foundation::Collections::IVector<ConfigurationParameter>& value)
    {
        THROW_HR_IF(E_POINTER, !value);
        m_parameters = value;
    }

    Windows::Foundation::Collections::ValueSet ConfigurationSet::Variables()
    {
        return m_variables;
    }

    void ConfigurationSet::Variables(const Windows::Foundation::Collections::ValueSet& value)
    {
        THROW_HR_IF(E_POINTER, !value);
        m_variables = value;
    }

    Windows::Foundation::Uri ConfigurationSet::SchemaUri()
    {
        return m_schemaUri;
    }

    void ConfigurationSet::SchemaUri(const Windows::Foundation::Uri& value)
    {
        THROW_HR_IF(E_INVALIDARG, !ConfigurationSetParser::IsRecognizedSchemaUri(value));
        m_schemaVersion = ConfigurationSetParser::GetSchemaVersionForUri(value);
        m_schemaUri = value;
    }

    HRESULT STDMETHODCALLTYPE ConfigurationSet::SetLifetimeWatcher(IUnknown* watcher)
    {
        return AppInstaller::WinRT::LifetimeWatcherBase::SetLifetimeWatcher(watcher);
    }
}
